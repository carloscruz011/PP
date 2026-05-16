#Carlos David Cruz Santiesteban 379909
#Practica 2: POO
import sys
import os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from flask import Flask, render_template, request, redirect, url_for
from models.ParkingLot import ParkingLot
from models.Vehicle import Car, Motorcycle

app = Flask(__name__)

# El modelo vive aqui, en memoria mientras el servidor este corriendo
lot = ParkingLot("UABC Parking")                


# ── Ruta 1: Dashboard ────────────────────────────────────────────────────────
@app.route("/")
def dashboard():
    ocupacion = lot.get_occupancy()
    tickets   = lot.get_active_tickets()
    return render_template("dashboard.html", ocupacion=ocupacion, tickets=tickets, lot=lot)


# ── Ruta 2: Formulario de entrada ────────────────────────────────────────────
@app.route("/entrada", methods=["GET"])
def entry_get():
    return render_template("entrada.html", error=None)


@app.route("/entrada", methods=["POST"])
def entry_post():
    placa = request.form.get("placa", "").strip().upper()
    tipo  = request.form.get("tipo", "")

    if not placa or tipo not in ("Car", "Motorcycle"):
        return render_template("entrada.html", error="Datos invalidos.")

    if tipo == "Car":
        vehicle = Car(placa)
    else:
        vehicle = Motorcycle(placa)

    ticket = lot.enter(vehicle)
    if ticket is None:
        return render_template("entrada.html", error="No hay spots disponibles.")

    return redirect(url_for("dashboard"))


# ── Ruta 3: Formulario de salida ─────────────────────────────────────────────
@app.route("/salida", methods=["GET"])
def salida_get():
    tickets = lot.get_active_tickets()
    return render_template("salida.html", tickets=tickets, error=None, costo=None)


@app.route("/salida", methods=["POST"])
def salida_post():
    try:
        ticket_id = int(request.form.get("ticket_id"))
        hours     = float(request.form.get("hours"))
    except (ValueError, TypeError):
        tickets = lot.get_active_tickets()
        return render_template("salida.html", tickets=tickets, error="Datos invalidos.", costo=None)

    costo = lot.exit(ticket_id, hours)
    if costo is None:
        tickets = lot.get_active_tickets()
        return render_template("salida.html", tickets=tickets, error="Ticket no encontrado.", costo=None)

    return redirect(url_for("dashboard"))


if __name__ == "__main__":
    app.run(debug=True)