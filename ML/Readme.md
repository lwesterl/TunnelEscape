# ML
Contains code for tensoflow model which was converted to tensoflow lite to be
run on the app

## Running

Install the requirements:

Depending on the OS (distro)
```
pip install -r requirements.txt
```
OR
```
pip3 install -r requirements.txt
```

The code will need some tweaking...
 - Set correct IP address to server.py
 - It should run on tensorflow v.2 but it uses legacy tensorflow v.1 api
   - Change tf.compat.v1 -> tf to run on tensorflow v.1

Run the local ML server:
```
python3 server.py
```

## Converting model
Use _convert_model.py_
- The model must first exist
- This needs some tweaking and the convert process has two steps (commenting/uncommenting code required)

## Note
* The model uses old tensorflow non-functional API which is basically deprecated (tensorflow v.1)
* It should be converted to use the Keras API for longevity
* The machine learning server implementation was never designed/intended to be run in production: it's only suitable for local model training
* In production the trained model is shipped with the app but some code has been
left in comments to support possible further model development (this mainly affects the app code itself making it messier)
