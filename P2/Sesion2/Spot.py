#Carlos David Cruz Santiesteban 379909
#Practica 2: POO
class ParkingSpot:
    def __init__(self, spot_id, allowed_type):
        self.__spot_id = spot_id
        self.__allowed_type = allowed_type  # "Car", "Motorcycle" o "Any"
        self.__occupied = False
        self.__current_vehicle = None

    def get_spot_id(self):
        return self.__spot_id
    
    def get_allowed_type(self):
        return self.__allowed_type
    
    def is_occupied(self):
        return self.__occupied
    
    def get_current_vehicle(self):
        return self.__current_vehicle
    
    def is_available_for(self, vehicle):
        if self.__occupied:
            return False
        if self.__allowed_type == "Any":
            return True
        return self.__allowed_type == vehicle.get_type()
    
    # Encapsulacion: solo se puede ocupar el lugar mediante este metodo
    def park(self, vehicle):
        if self.__occupied:
            print(f"  Error: el spot {self.__spot_id} ya esta ocupado.")
            return False
        self.__current_vehicle = vehicle
        self.__occupied = True
        return True
    
    def release(self):
        self.__current_vehicle = None
        self.__occupied = False
 
    def __str__(self):
        if self.__occupied:
            return f"[{self.__spot_id}] Ocupado por {self.__current_vehicle}"
        return f"[{self.__spot_id}] Libre ({self.__allowed_type})"