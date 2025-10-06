package load_balancer

import (
	"fmt"
	"net/http"
	"net/http/httputil"
	"net/url"
	"os"
)

// Server interface defines behavior of a backend server
type Server interface {
	Address() string                          // Returns server address
	IsAlive() bool                            // Checks if server is alive
	Serve(http.ResponseWriter, *http.Request) // Proxies the request to the server
}

// simpleServer is a concrete implementation of the Server interface
type simpleServer struct {
	addr  string
	proxy *httputil.ReverseProxy
}

// Address returns the server address
func (s *simpleServer) Address() string {
	return s.addr
}

// IsAlive returns true (can be expanded to health check)
func (s *simpleServer) IsAlive() bool {
	return true
}

// Serve handles the incoming HTTP request and proxies it to the backend
func (s *simpleServer) Serve(rw http.ResponseWriter, req *http.Request) {
	s.proxy.ServeHTTP(rw, req)
}

// newSimpleServer initializes a simpleServer with a reverse proxy
func newSimpleServer(addr string) *simpleServer {
	serverUrl, err := url.Parse(addr)
	handleErr(err)

	return &simpleServer{
		addr:  addr,
		proxy: httputil.NewSingleHostReverseProxy(serverUrl),
	}
}

// LoadBalancer handles distributing traffic among backend servers
type LoadBalancer struct {
	port            string   // Port to listen on
	roundRobinCount int      // Counter for round-robin selection
	servers         []Server // List of backend servers
}

// NewLoadBalancer initializes a load balancer with given port and server list
func NewLoadBalancer(port string, servers []Server) *LoadBalancer {
	return &LoadBalancer{
		port:            port,
		roundRobinCount: 0,
		servers:         servers,
	}
}

// handleErr prints the error and exits if an error occurred
func handleErr(err error) {
	if err != nil {
		fmt.Printf("error: %v\n", err)
		os.Exit(1)
	}
}

// getNextAvailableServer selects the next alive server using round-robin
// Time complexity : O(n)
// Space complexity : O(1)
// if all previous servers are down and we loop through multiple times.
func (lb *LoadBalancer) getNextAvailableServer() Server {
	server := lb.servers[lb.roundRobinCount%len(lb.servers)]
	for !server.IsAlive() {
		lb.roundRobinCount++
		server = lb.servers[lb.roundRobinCount%len(lb.servers)]
	}
	lb.roundRobinCount++

	return server
}

// serveProxy forwards the HTTP request to a selected backend server

func (lb *LoadBalancer) serveProxy(rw http.ResponseWriter, req *http.Request) {
	targetServer := lb.getNextAvailableServer()

	fmt.Printf("forwarding request to address %q\n", targetServer.Address())

	targetServer.Serve(rw, req)
}

// main function starts the HTTP server and initializes the load balancer
func main() {
	// Define backend servers here
	servers := []Server{
		newSimpleServer("http://localhost:9001"),
		// newSimpleServer("http://localhost:9002"),
		// newSimpleServer("http://localhost:9003"),
	}

	// Create a new load balancer
	lb := NewLoadBalancer("8000", servers)

	// Define the handler to forward incoming requests
	handleRedirect := func(rw http.ResponseWriter, req *http.Request) {
		lb.serveProxy(rw, req)
	}

	// Register the handler for root path
	http.HandleFunc("/", handleRedirect)

	fmt.Printf("serving requests at 'localhost:%s'\n", lb.port)

	// Start HTTP server
	err := http.ListenAndServe(":"+lb.port, nil)
	handleErr(err)
}
