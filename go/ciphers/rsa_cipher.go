// Description:This Go program generates an RSA key pair, encrypts a message using the public key with OAEP padding and SHA-256, and then decrypts it using the private key to recover the original message.

package rsa_cipher

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/sha256"
	"fmt"
)

func main() {
	// Step 1: Generate RSA Key Pair (2048 bits)
	//Time complexity : O(k^3) where k is size of the key in bits
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		panic(err)
	}
	publicKey := &privateKey.PublicKey

	// Step 2: Encrypt a message using the public key
	//Time complexity : O(k^2)
	message := []byte("Hello, RSA in Go!")
	label := []byte("") // Optional label for OAEP
	hash := sha256.New()

	ciphertext, err := rsa.EncryptOAEP(hash, rand.Reader, publicKey, message, label)
	if err != nil {
		panic(err)
	}
	fmt.Printf("Encrypted message: %x\n", ciphertext)

	// Step 3: Decrypt the message using the private key
	//Time complexity : O(k^3)
	plaintext, err := rsa.DecryptOAEP(hash, rand.Reader, privateKey, ciphertext, label)
	if err != nil {
		panic(err)
	}
	fmt.Printf("Decrypted message: %s\n", string(plaintext))
}
