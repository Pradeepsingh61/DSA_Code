from flask import Flask, request, jsonify
import json

app = Flask(__name__)
DATA_FILE = 'products.json'

def load_data():
    try:
        with open(DATA_FILE, 'r') as f:
            return json.load(f)
    except:
        return []

def save_data(data):
    with open(DATA_FILE, 'w') as f:
        json.dump(data, f, indent=2)

@app.route('/products', methods=['GET'])
def get_products():
    return jsonify(load_data())

@app.route('/products/<int:product_id>', methods=['GET'])
def get_product(product_id):
    product = next((p for p in load_data() if p['id'] == product_id), None)
    if product:
        return jsonify(product)
    return jsonify({'message': 'Product not found'}), 404

@app.route('/products', methods=['POST'])
def create_product():
    products = load_data()
    new_product = request.json
    new_product['id'] = max([p['id'] for p in products], default=0) + 1
    products.append(new_product)
    save_data(products)
    return jsonify(new_product), 201

@app.route('/products/<int:product_id>', methods=['PUT'])
def update_product(product_id):
    products = load_data()
    product = next((p for p in products if p['id'] == product_id), None)
    if product:
        product.update(request.json)
        save_data(products)
        return jsonify(product)
    return jsonify({'message': 'Product not found'}), 404

@app.route('/products/<int:product_id>', methods=['DELETE'])
def delete_product(product_id):
    products = load_data()
    product = next((p for p in products if p['id'] == product_id), None)
    if product:
        products.remove(product)
        save_data(products)
        return jsonify({'message': 'Product deleted'})
    return jsonify({'message': 'Product not found'}), 404

if __name__ == '__main__':
    save_data(load_data())
    app.run(debug=True)
