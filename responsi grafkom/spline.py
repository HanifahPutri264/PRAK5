import numpy as np
from scipy.interpolate import CubicSpline
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# === TITIK-TITIK UTAMA ===
bottom_bracket = np.array([0, 0, 0])
seat_top = np.array([-0.1, 1.2, 0])
handlebar_base = np.array([1.5, 1, 0])
front_axle = np.array([1.8, 0, 0])
rear_axle = np.array([-0.8, 0, 0])

# === RANGKA SEPEDA ===
def draw_spline(p1, p2, via=None, color='black', label=None):
    """Buat spline halus antara dua titik (bisa pakai titik via tengah)."""
    if via is None:
        points = np.vstack([p1, p2])
        t = np.linspace(0, 1, 2)
    else:
        points = np.vstack([p1, via, p2])
        t = np.linspace(0, 1, 3)
    
    cs_x = CubicSpline(t, points[:, 0])
    cs_y = CubicSpline(t, points[:, 1])
    cs_z = CubicSpline(t, points[:, 2])
    ts = np.linspace(0, 1, 100)
    ax.plot(cs_x(ts), cs_y(ts), cs_z(ts), color=color, label=label)

# Segitiga utama
draw_spline(bottom_bracket, seat_top, color='black')         # Seat tube
draw_spline(seat_top, handlebar_base, color='black')         # Top tube
draw_spline(handlebar_base, bottom_bracket, color='black')   # Down tube

# Seat stay dan chain stay
draw_spline(seat_top, rear_axle, color='gray')
draw_spline(bottom_bracket, rear_axle, color='gray')

# Fork depan (2 garis ke roda depan)
draw_spline(bottom_bracket, front_axle, color='gray')
draw_spline(handlebar_base, front_axle, color='gray')

# === STANG LENGKUNG ===
stang_l = handlebar_base + np.array([-0.3, 0.05, 0])
stang_r = handlebar_base + np.array([0.3, 0.05, 0])
draw_spline(stang_l, stang_r, via=handlebar_base, color='blue', label="Stang")

# === RODA ===
def draw_wheel(center, r=0.3, color='gray'):
    theta = np.linspace(0, 2 * np.pi, 100)
    x = center[0] + r * np.cos(theta)
    y = center[1] + r * np.sin(theta)
    z = np.full_like(x, center[2])
    ax.plot(x, y, z, color=color)

draw_wheel(rear_axle)
draw_wheel(front_axle)

# === SADEL (Permukaan Mesh) ===
x_sadel = [seat_top[0] - 0.1, seat_top[0] + 0.1, seat_top[0] + 0.1, seat_top[0] - 0.1]
y_sadel = [seat_top[1], seat_top[1], seat_top[1] + 0.2, seat_top[1] + 0.2]
z_sadel = [0, 0, 0, 0]
ax.plot_trisurf(x_sadel, y_sadel, z_sadel, color='brown', alpha=0.9)

# === PENGATURAN TAMPILAN ===
ax.set_title("Model Sepeda (Spline + Mesh)")
ax.set_xlim(-1, 2.5)
ax.set_ylim(-0.5, 2.5)
ax.set_zlim(-0.5, 1)
ax.view_init(elev=20, azim=-60)
ax.set_box_aspect([3, 2, 1])
plt.legend()
plt.show()
