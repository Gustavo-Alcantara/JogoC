from scipy.io import wavfile as wav
import numpy as np
import time
import matplotlib.pyplot as plt

rate, data = wav.read('sound.wav')

tamanho = data.shape[0]
data_mono = [data[j][0] for j in range(tamanho)]
mini_fft = np.zeros(10)
mini_fft = np.fft.fft(data[100000:110000])
antes = time.time() 
spectro = np.array([np.argmax(np.fft.rfft(data[i:i+100])) for i in range(0,tamanho-100,100) ])
depois = time.time()
tempo = depois - antes
