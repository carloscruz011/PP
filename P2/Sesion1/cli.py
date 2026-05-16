#Carlos David Cruz Santiesteban 379909
#Practica 2: POO
import sys
import os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from ParkingLot import ParkingLot
from Vehicle import Car, Motorcycle

def mostrar_menu(lot):
    print("\n" + "=" * 45)
    print(f"  {lot.get_name()}")
    print(f"  Tarifa: {lot.get_policy().describe()}")
    print(f"  Recaudado: ${lot.get_total_revenue()}")
    print("=" * 45)
    print("  [1] Registrar entrada")
    print("  [2] Registrar salida")
    print("  [3] Ver ocupacion")
    print("  [4] Ver tickets activos")
    print("  [0] Salir")
    print("=" * 45)
 
 
def registrar_entrada(lot):
    print("\n-- REGISTRAR ENTRADA --")
    plate = input("  Placa: ").strip().upper()
    print("  Tipo: [1] Car  [2] Motorcycle")
    tipo = input("  Elige: ").strip()
 
    if tipo == "1":
        vehicle = Car(plate)
    elif tipo == "2":
        vehicle = Motorcycle(plate)
    else:
        print("  Tipo invalido.")
        return
 
    ticket = lot.enter(vehicle)
    if ticket:
        print(f"  Entrada registrada: {ticket}")
 
 
def registrar_salida(lot):
    print("\n-- REGISTRAR SALIDA --")
 
    if len(lot.get_active_tickets()) == 0:
        print("  No hay vehiculos estacionados.")
        return
 
    print("  Tickets activos:")
    lot.show_active_tickets()
 
    try:
        ticket_id = int(input("  Numero de ticket: ").strip())
        hours = float(input("  Horas estacionado: ").strip())
    except ValueError:
        print("  Valor invalido.")
        return
 
    cost = lot.exit(ticket_id, hours)
    if cost is not None:
        print(f"  Salida registrada. Costo: ${cost}")
 
 
def main():
    lot = ParkingLot("UABC Parking")
 
    while True:
        mostrar_menu(lot)
        opcion = input("  Elige una opcion: ").strip()
 
        if opcion == "1":
            registrar_entrada(lot)
        elif opcion == "2":
            registrar_salida(lot)
        elif opcion == "3":
            print("\n-- OCUPACION --")
            lot.show_occupancy()
        elif opcion == "4":
            print("\n-- TICKETS ACTIVOS --")
            lot.show_active_tickets()
        elif opcion == "0":
            print("\n  Hasta luego.")
            break
        else:
            print("  Opcion no valida.")
 
 
if __name__ == "__main__":
    main()