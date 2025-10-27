from flask import Flask, request, jsonify
import json

app = Flask(__name__)
DATA_FILE = 'users.json'

def read_users():
    with open(DATA_FILE, 'r') as f:
        return json.load(f)

def write_users(users):
    with open(DATA_FILE, 'w') as f:
        json.dump(users, f, indent=2)

@app.route('/users', methods=['GET'])
def get_users():
    users = read_users()
    return jsonify(users)

@app.route('/users/<int:user_id>', methods=['GET'])
def get_user(user_id):
    users = read_users()
    user = next((u for u in users if u['id'] == user_id), None)
    if user:
        return jsonify(user)
    return jsonify({'message': 'User not found'}), 404

@app.route('/users', methods=['POST'])
def create_user():
    users = read_users()
    new_user = request.json
    new_user['id'] = max([u['id'] for u in users], default=0) + 1
    users.append(new_user)
    write_users(users)
    return jsonify(new_user), 201

@app.route('/users/<int:user_id>', methods=['PUT'])
def update_user(user_id):
    users = read_users()
    user = next((u for u in users if u['id'] == user_id), None)
    if user:
        data = request.json
        user.update(data)
        write_users(users)
        return jsonify(user)
    return jsonify({'message': 'User not found'}), 404

@app.route('/users/<int:user_id>', methods=['DELETE'])
def delete_user(user_id):
    users = read_users()
    user = next((u for u in users if u['id'] == user_id), None)
    if user:
        users.remove(user)
        write_users(users)
        return jsonify({'message': 'User deleted'})
    return jsonify({'message': 'User not found'}), 404

if __name__ == '__main__':
    try:
        open(DATA_FILE, 'r')
    except:
        with open(DATA_FILE, 'w') as f:
            json.dump([], f)
    app.run(debug=True)
