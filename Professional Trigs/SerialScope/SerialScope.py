import serial
import pyqtgraph as pg
from PyQt5 import QtWidgets, QtCore
import sys
import time
import threading

serial_port = 'COM3'
baud_rate = 256000
ser = serial.Serial(serial_port, baud_rate, timeout=1)

app = QtWidgets.QApplication([])


main_win = QtWidgets.QWidget()
main_win.setWindowTitle("Real-time Serial Plot with Pause/Resume")
main_layout = QtWidgets.QVBoxLayout()
main_win.setLayout(main_layout)


control_panel = QtWidgets.QWidget()
control_layout = QtWidgets.QHBoxLayout()
control_panel.setLayout(control_layout)

pause_button = QtWidgets.QPushButton("Pause")
control_layout.addWidget(pause_button)


plot_widget = pg.GraphicsLayoutWidget()
plot = plot_widget.addPlot(title="Serial Input")
curve = plot.plot(pen='y')

plot.setMouseEnabled(x=True, y=False)

main_layout.addWidget(control_panel)
main_layout.addWidget(plot_widget)

data_buffer = [float('nan')] * 300
max_points = 300
last_data_time = 0
timeout_threshold = 2.0

lock = threading.Lock()
paused = False

def serial_thread_func():
    global last_data_time
    while True:
        try:
            line = ser.readline()
            value = line.decode('utf-8', errors='replace').strip()
            if value:
                try:
                    val = float(value)
                    with lock:
                        if not paused:
                            data_buffer.append(val)
                            if len(data_buffer) > max_points:
                                data_buffer.pop(0)
                    last_data_time = time.time()
                except ValueError:
                    pass
        except Exception as e:
            print("Serial error:", e)
            time.sleep(1)

def update():
    now = time.time()
    with lock:
        if now - last_data_time > timeout_threshold and not paused:
            data_buffer.append(float('nan'))
            if len(data_buffer) > max_points:
                data_buffer.pop(0)
        if not paused:
            curve.setData(data_buffer)

def toggle_pause():
    global paused
    paused = not paused
    pause_button.setText("Resume" if paused else "Pause")

pause_button.clicked.connect(toggle_pause)

serial_thread = threading.Thread(target=serial_thread_func, daemon=True)
serial_thread.start()

timer = QtCore.QTimer()
timer.timeout.connect(update)
timer.start(50)

main_win.show()
sys.exit(app.exec_())
