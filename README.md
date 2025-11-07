# Sistemas Operativos Avanzados Práctica 2: Computación Matricial

## Participantes

Calos Oramas y Mario Gonzalo

## 3 Time Secuencial

<img width="587" height="573" alt="image" src="https://github.com/user-attachments/assets/0ad4fc4b-23fd-45bc-b8fa-db86c1bb5810" />

<img width="577" height="570" alt="image" src="https://github.com/user-attachments/assets/f914499d-65ad-45b2-a525-35ba4062337f" />

En estas dos capturas se puede observar el tiempo de ejecución de ambos procesos secuenciales donde los tiempos son prácticamente iguales ya que en hebSecuencial solo hay una hebra activa por lo que al usarla de forma secuencial no aporta paralelismo.

## 6 Time Concurrente

<img width="582" height="572" alt="image" src="https://github.com/user-attachments/assets/b23fcbc9-6e6c-4e85-8e2c-2b24e53902fd" />

<img width="613" height="551" alt="image" src="https://github.com/user-attachments/assets/6eccaa6f-3b6f-4985-a699-0684d052e95a" />

En estos casos ambos procesos son más rápidos que sus versiones secuenciales. hebConcurrente es más rápido que su contraparte de procesos ya que crear hebras es más ligero que procesos ya que comparten el mismo espacio de memoria y recursos.
Por otra parte procConcurrente también mejora sobre procSecuencial pero su coste de creación y sincronización de procesos es algo mayor.


