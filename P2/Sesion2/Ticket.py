#Carlos David Cruz Santiesteban 379909
#Practica 2: POO
class Ticket:
    def __init__(self, ticket_id, vehicle, spot):
        self.__ticket_id = ticket_id
        self.__vehicle = vehicle
        self.__spot = spot
        self.__hours = None
        self.__cost = None
        self.__active = True
 
    def get_ticket_id(self):
        return self.__ticket_id
 
    def get_vehicle(self):
        return self.__vehicle
 
    def get_spot(self):
        return self.__spot
 
    def get_hours(self):
        return self.__hours
 
    def get_cost(self):
        return self.__cost
 
    def is_active(self):
        return self.__active
 
    # Cierra el ticket con las horas que estuvo el vehiculo
    def close(self, hours, cost):
        self.__hours = hours
        self.__cost = cost
        self.__active = False
 
    def __str__(self):
        status = "ACTIVO" if self.__active else f"CERRADO ({self.__hours}h - ${self.__cost})"
        return f"Ticket #{self.__ticket_id} | {self.__vehicle} | Spot {self.__spot.get_spot_id()} | {status}"
    