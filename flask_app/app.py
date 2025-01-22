from flask import Flask, request, jsonify, render_template

app = Flask(__name__)

# Store data in memory
sensor_data = {}

@app.route('/')
def index():
    return render_template('index.html', data=sensor_data)

@app.route('/data', methods=['POST'])
def receive_data():
    global sensor_data
    if request.method == 'POST':
        sensor_data = request.get_json()
        print("Received data:", sensor_data)
        return jsonify({"status": "success", "message": "Data received successfully"}), 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
