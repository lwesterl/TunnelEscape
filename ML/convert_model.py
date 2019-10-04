import tensorflow as tf


'''
Script for converting model first to .pb file and then to tensorflow lite model
Commented section contains code for creating a folder that can be viewed by tensorboard
'''
def convert_model():
    meta_path = 'model.ckpt.meta'
    output_file = 'output_graph.pb'
    lite_file = 'model_final.lite'


    with tf.Session() as sess:
        # Restore the graph
        saver = tf.compat.v1.train.import_meta_graph(meta_path)

        # Load weights
        saver.restore(sess,tf.compat.v1.train.latest_checkpoint(''))
        output_node_names = ['Placeholder', 'flatten/Reshape', 'dense/BiasAdd', 'dense_1/BiasAdd', 'dense_2/BiasAdd', 'dense_3/BiasAdd'] # found by: tensorboard --logdir __tb

        # Freeze the graph
        frozen_graph_def = tf.compat.v1.graph_util.convert_variables_to_constants(
            sess,
            sess.graph_def,
            output_node_names)

        # Save the frozen graph
        with open(output_file, 'wb') as f:
            f.write(frozen_graph_def.SerializeToString())

        converter = tf.lite.TFLiteConverter.from_frozen_graph(output_file, ['Placeholder'], ['dense_3/Bias'])
        lite_model = converter.convert()
        with open(lite_file, 'wb') as f:
            f.write(lite_model)


        interpreter = tf.lite.Interpreter(model_content=lite_model)
        interpreter.allocate_tensors()

        '''
        # Create tb folder for tensorboard
        from tensorflow.summary import FileWriter

        sess = tf.Session()
        tf.train.import_meta_graph(meta_path)
        FileWriter("__tb", sess.graph)'''





if __name__ == '__main__':
    convert_model()
