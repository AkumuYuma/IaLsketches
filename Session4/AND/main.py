import numpy as np
import pandas as pd
from and_network import Perceptron


def generate_Datas(lunghezza):
    datas = pd.DataFrame()
    datiA = np.random.randint(0, 2, lunghezza)
    datiB = np.random.randint(0, 2, lunghezza)
    datas["a"] = pd.Series(datiA)
    datas["b"] = pd.Series(datiB)
    datas["label"] = datas.apply(lambda riga: riga["a"] & riga["b"], axis = 1)
    return datas


if __name__ == "__main__":
    neuron = Perceptron(2)
    # a.set_pesi(np.array([-1,2,2]))

    dati = generate_Datas(10)

    a = dati["a"]
    b = dati["b"]

    inputs = np.stack((np.array(a), np.array(b)), axis = 1)
    labels = np.array(dati["label"]).reshape(-1, 1)

    print(neuron)

    for i in range(10000):
        neuron.train(inputs,labels)

    print(neuron)




