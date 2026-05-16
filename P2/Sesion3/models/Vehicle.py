#Carlos David Cruz Santiesteban 379909
#Practica 2: POO
class Vehicle:
    def __init__(self, plate, vehicle_type):
        self.__plate = plate
        self.__type = vehicle_type

    def get_plate(self):
        return self.__plate
    
    def get_type(self):
        return self.__type
    
    def get_type(self):
        return self.__type
 
    def __str__(self):
        return f"{self.__type} - {self.__plate}"

# Las siguientes dos clases heredan de vehicle  
class Car(Vehicle):
    def __init__(self, plate):
        super().__init__(plate, "Car")

class Motorcycle(Vehicle):
    def __init__(self, plate):
        super().__init__(plate, "Motorcycle")