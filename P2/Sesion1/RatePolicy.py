#Carlos David Cruz Santiesteban 379909
#Practica 2: POO
class RatePolicy:
    def __init__(self, car_rate = 20, moto_rate = 10):
        self.__car_rate = car_rate
        self.__moto_rate = moto_rate

    def calculate(self, hours, vehicle):
        if vehicle.get_type() == "Car":
            return hours * self.__car_rate
        else:
            return hours * self.__moto_rate
 
    def describe(self):
        return f"Auto: ${self.__car_rate}/h | Moto: ${self.__moto_rate}/h"