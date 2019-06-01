import random
import base64

# class data


class Data:

    ImageNum = 0
    IMAGENAME_PREFIX = 'training/data'
    ImageNumFile = 'ImageNum.txt'

    '''
    Create image file from base64 encoded string, static method
    Call this from add_data to create new image (state representation)
    imageStr: image in base64 string format
    '''
    @staticmethod
    def create_image(imageStr):
        imgdata = base64.b64decode(imageStr)
        filename = Data.IMAGENAME_PREFIX + str(Data.ImageNum) + '.png' # save with unique names
        with open(filename, 'wb') as f:
            f.write(imgdata)
        Data.ImageNum += 1
        return filename

    '''
    Call this to update ImageNum to match previous value
    (this should be called when server is started)
    '''
    @staticmethod
    def init_ImageNum():
        with open(Data.ImageNumFile, 'r') as file:
            imageNumStr = file.read()
            Data.ImageNum = int(imageNumStr.strip('\n'))
            print('Starting from image nro: ', Data.ImageNum)

    '''
    Call this to store ImageNum value to file
    (this should be called when server quits)
    '''
    @staticmethod
    def store_ImageNum():
        with open(Data.ImageNumFile, 'w') as file:
            file.write(str(Data.ImageNum + 1))

    '''
    Init Data object, remember to keep this object alive (create when program starts)
    Data object contains all data needed to train the network
    '''
    def __init__(self):
        self.__max_data = 10000
        self.__data = []
        self.__current_imagename = ''
        self.__prev_imagename = ''
        self.__rewards = {}
        self.__actions = {}
        random.seed(None)

    '''
    Add image filename to data list
    Call this from server when new image arrives in string format
    imageStr: image in base64 string format
    '''
    def add_data(self, imageStr):
        self.__prev_imagename = self.__current_imagename
        self.__current_imagename = Data.create_image(imageStr)
        self.__data.append(self.__current_imagename)
        if len(self.__data) > self.__max_data:
            imagename = self.__data.pop(0)
            self.__rewards.pop(imagename, None)
            self.__actions.pop(imagename, None)

    '''
    add action to actions, call this after it's clear what action was taken
    action: action that was executed previously
    '''
    def add_action(self, action):
        self.__actions[self.__current_imagename] = action

    '''
    add reward to dictinary, call this after it's clear what reward previous
    action caused
    reward: latest response to the executed action
    '''
    def add_reward(self, reward):
        if self.__current_imagename != '' and self.__current_imagename not in self.__rewards:
            # allow only reward insertion once
            self.__rewards[self.__current_imagename] = reward
        if self.__prev_imagename != '':
            self.__rewards[self.__prev_imagename] += reward # strong correlation between previous and current state

    '''
    Get random data sample as tuple (state(filename), action, reward, next state(filename))
    start: index from rand is started
    end: index to which rand is ended
    return: (state(filename), action, reward, next state(filename)), None if there isn't enough items in the list
    '''
    def get_random_data(self, start=None, end=None):
        state = None
        next_state = None
        reward = None
        action = None
        try:
            index = 0
            if start and end:
                index = random.randrange(start, end)
            else:
                index = random.randrange(0, len(self.__data) - 2)
            try:
                state = self.__data[index]
                next_state = self.__data[index + 1]
                action = self.__actions[state]
                reward = self.__rewards[state]
            except KeyError:
                return None
        except ValueError:
            return None

        return (state, action, reward, next_state)

    '''
    Wrapper call for get_random_data which return specific data sample
    index: tells sample index
    return: (state, action, reward, next_state), None if non-valid index
    '''
    def get_data(self, index):
        return get_random_data(index, index + 1)

    '''
    Get training data for the neural network
    data_amount: training patch size
    return: data_amount of randomly selected data or as much data as is available, if no
    training data available, empty list is returned
    NOTICE: the last data item won't have next_state available so it can't be yet used for training
    '''
    def get_training_data(self, data_amount):
        data_array = []
        length = data_amount
        if data_amount > len(self.__data) - 2:
            length = len(self.__data) - 2
        #for _ in range(length):
        #data_array.append(self.get_random_data())
        if len(self.__data) - 2 > 0:
            states = random.sample(self.__data[: - 2], length)
            for state in states:
                data_array.append((state, self.__actions[state], self.__rewards[state], self.get_next_state(state)))

        return data_array

    '''
    Get the next state, slow but should work
    '''
    def get_next_state(self, cmpState):
        for i, state in enumerate(self.__data):
            if state == cmpState:
                try:
                    return self.__data[i + 1]
                except KeyError as e:
                    print(e)
                    return cmpState # no good options left

    '''
    Get current state
    return: __current_imagename which tells correct path to image which represent current state
    '''
    def get_current_state(self):
        return self.__current_imagename
