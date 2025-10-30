import numpy as np
from scipy.interpolate import CubicSpline
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# === TITIK KUNCI ===
bottom_bracket = np.array([0, 0, 0])
seat_tube_top = np.array([0, 1, 0])
head_tube_top = np.array([1.5, 1, 0])
front_axle = np.array([1.8, 0, 0])
rear_axle = np.array([-0.8, 0, 0])

# === RANGKA SEPEDA ===
def spline_line(p1, p2, label=None, color='black'):
    points = np.vstack([p1, p2])
    t = np.linspace(0, 1, 2)
    cs_x = CubicSpline(t, points[:, 0])
    cs_y = CubicSpline(t, points[:, 1])
    cs_z = CubicSpline(t, points[:, 2])
    ts = np.linspace(0, 1, 100)
    ax.plot(cs_x(ts), cs_y(ts), cs_z(ts), color=color, label=label)

# Rangka utama
spline_line(bottom_bracket, seat_tube_top)        # seat tube
spline_line(seat_tube_top, head_tube_top)         # top tube
spline_line(head_tube_top, bottom_bracket)        # down tube

# Chain stay & seat stay
spline_line(bottom_bracket, rear_axle, color='gray')
spline_line(seat_tube_top, rear_axle, color='gray')

# Fork ke roda depan
spline_line(bottom_bracket, front_axle, color='gray')
spline_line(head_tube_top, front_axle, color='gray')

# === RODA ===
def draw_wheel(center, r=0.3, color='gray'):
    theta = np.linspace(0, 2 * np.pi, 100)
    x = center[0] + r * np.cos(theta)
    y = center[1] + r * np.sin(theta)
    z = np.full_like(x, center[2])
    ax.plot(x, y, z, color=color)

draw_wheel(rear_axle)
draw_wheel(front_axle)

# === SADEL ===
x_sadel = [seat_tube_top[0] - 0.1, seat_tube_top[0] + 0.1,
           seat_tube_top[0] + 0.1, seat_tube_top[0] - 0.1]
y_sadel = [seat_tube_top[1], seat_tube_top[1],
           seat_tube_top[1] + 0.2, seat_tube_top[1] + 0.2]
z_sadel = [0, 0, 0, 0]
ax.plot_trisurf(x_sadel, y_sadel, z_sadel, color='brown', alpha=0.8)

# === STANG ===
# Buat stang horizontal ke kiri dan kanan dari head_tube_top
handlebar_length = 0.6
left_end = head_tube_top + np.array([-handlebar_length/2, 0, 0])
right_end = head_tube_top + np.array([handlebar_length/2, 0, 0])
spline_line(left_end, right_end, label='Stang', color='darkblue')

# === TAMPILKAN ===
ax.set_title("Model Sepeda Lengkap (dengan Stang)")
ax.set_xlim(-1, 2.5)
ax.set_ylim(-1, 2.5)
ax.set_zlim(-1, 1)
ax.set_box_aspect([3, 2, 1])
plt.legend()
plt.show()
