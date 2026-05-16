#Carlos David Cruz Santiesteban 379909
#Practica 2: POO
from models.Spot import ParkingSpot
from models.Ticket import Ticket
from models.RatePolicy import HourlyRatePolicy # Cambio de Sesion 2

class ParkingLot:
    def __init__(self, name):
        self.__name = name
        self.__spots = []           # lista de ParkingSpot  -> Composicion
        self.__active_tickets = []  # lista de Ticket activos
        self.__next_ticket_id = 1
        self.__total_revenue = 0
        self.__policy = HourlyRatePolicy()  # Cambio de Sesion 2

        # Espacio para 6 carros y 4 motos
        for i in range(1, 7):
            self.__spots.append(ParkingSpot(f"A{i}", "Car"))
        for i in range(1, 5):
            self.__spots.append(ParkingSpot(f"M{i}", "Motorcycle"))

    def enter(self, vehicle):
        spot = None
        for s in self.__spots:
            if s.is_available_for(vehicle):
                spot = s
                break

        if spot is None:
            print("  No hay spots disponibles para este tipo de vehiculo.")
            return None
        
        spot.park(vehicle)
        ticket = Ticket(self.__next_ticket_id, vehicle, spot)
        self.__active_tickets.append(ticket)
        self.__next_ticket_id += 1
        return ticket
    
    def exit(self, ticket_id, hours):
        # Buscar el ticket activo
        ticket = None
        for t in self.__active_tickets:
            if t.get_ticket_id() == ticket_id:
                ticket = t
                break
 
        if ticket is None:
            print(f"  No se encontro el ticket #{ticket_id}.")
            return None
 
        # Calcular costo y cerrar ticket
        cost = self.__policy.calculate(hours, ticket.get_vehicle())
        ticket.close(hours, cost)
        ticket.get_spot().release()
        self.__active_tickets.remove(ticket)
        self.__total_revenue += cost
        return cost
    
    def show_occupancy(self):
        occupied = 0
        for s in self.__spots:
            if s.is_occupied():
                occupied += 1
        free = len(self.__spots) - occupied
        print(f"  Total: {len(self.__spots)} | Libres: {free} | Ocupados: {occupied}")
        print()
        for s in self.__spots:
            print(f"    {s}")

    def show_active_tickets(self):
        if len(self.__active_tickets) == 0:
            print("  No hay vehiculos estacionados.")
            return
        for t in self.__active_tickets:
            print(f"    {t}")

    def get_occupancy(self):
        occupied = 0
        for s in self.__spots:
            if s.is_occupied():
                occupied += 1
        free = len(self.__spots) - occupied
        return {"total": len(self.__spots), "free": free, "occupied": occupied}
    
    def get_spots(self):
        return self.__spots
 
    def get_name(self):
        return self.__name
 
    def get_total_revenue(self):
        return self.__total_revenue
 
    def get_active_tickets(self):
        return self.__active_tickets
 
    def get_policy(self):
        return self.__policy
    
    def set_policy(self, policy):
        self.__policy = policy