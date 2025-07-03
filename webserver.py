import os
from dotenv import load_dotenv
from flask import Flask, request, jsonify
from pymongo import MongoClient

load_dotenv()
IP = os.getenv("IPV4")
DB = os.getenv("DB")
client = MongoClient()
client = MongoClient(DB, 27017)
db = client.sensor_data
collection = db.temperature_values

app = Flask(__name__)


@app.route("/")
def hello_world():
    return "<p>Test</p>"

@app.post("/data")
def receive_data():
    data = request.get_json()
    print(data)
    try:
        collection.insert_one(data)
        print("Write successful!")
    except:
        print("Error updating database!")
    return jsonify(200)

@app.get("/query")
def get_data():
    return_list = []
    values = list(db.temperature_values.find()) #values: list of dicts
    for value in values:
        return_data = {}
        return_data["Time"] = str(value["Time"])
        return_data["Temperature"] = str(value["Temperature"])
        return_list.append(return_data)
    return jsonify(return_list)

if __name__ == '__main__':
    app.run(host=IP, port=5000, debug=True)