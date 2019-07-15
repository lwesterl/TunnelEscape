# ML
Contains code for tensoflow model which was converted to tensoflow lite to be
run on the app

## Note
* The model uses old tensoflow non-functional API which is basically deprecated
* It should be converted to use the Keras API for longevity
* The machine learning server implementation was never designed/intended to be run in production: it's only suitable for local model training
* In production the trained model is shipped with the app but some code has been
left in comments to support possible further model development (this mainly affects the app code itself making it messier)
