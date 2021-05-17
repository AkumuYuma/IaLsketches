# Voglio creare una nn con un solo perceptron che modellizzi l'and logico

import numpy as np
import pandas as pd


class Perceptron:
    def __init__(self, n):
        # Riceve un numero di input e inizializza pesi casuali
        self._n = n
        self._pesi = np.random.uniform(low=-1, high=1, size=(n + 1, 1))

    def set_pesi(self, pesi):
        if pesi.shape != (self._n + 1, 1):
            pesi = pesi.reshape(self._n + 1, 1)
        self._pesi = pesi

    def guess(self, inputs):
        # :param: array di numpy come inputs
        # :return: guess
        # Appendo il bias
        input_layer = np.array([1])
        input_layer = np.append(input_layer, inputs)
        value = S(np.matmul(input_layer, self._pesi)[0])
        if value > 0.5: return 1
        else: return 0

    def __str__(self):
        return f"{self._pesi}"

    def cambia_pesi(self, errore, inp):
        self._pesi[0] += error * learning_rate
        self._pesi[1] += (error * inp[0]) * learning_rate
        self._pesi[2] += (error * inp[1]) * learning_rate

    def gradient_descend(self, errors, inputs):
        learning_rate = 0.5
        np.apply_along_axis(self.cambia_pesi, 0, (errors, inputs))

    def train(self, inputs, labels):
        guesses = np.apply_along_axis(self.guess, 1, inputs)
        errors = (labels - guesses.reshape(-1, 1))
        self.gradient_descend(errors, inputs)



def S(x):
    return 1 / (1 + np.exp(-x))
