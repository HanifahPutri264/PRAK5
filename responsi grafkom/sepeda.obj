import trimesh
import numpy as np
from scipy.interpolate import splprep, splev

# Titik spline rangka sepeda
control_points = np.array([
    [-0.5, 0.0, 0.0],
    [-0.2, 0.4, 0.0],
    [0.4, 0.4, 0.0],
    [0.6, 0.2, 0.0]
])

# Interpolasi spline
tck, _ = splprep(control_points.T, s=0)
u = np.linspace(0, 1, 100)
x, y, z = splev(u, tck)
spline_points = np.vstack((x, y, z)).T

# Buat silinder kecil mengikuti spline
def create_cylinder_between(p1, p2, radius=0.025, sections=12):
    vec = np.array(p2) - np.array(p1)
    height = np.linalg.norm(vec)
    cyl = trimesh.creation.cylinder(radius=radius, height=height, sections=sections)
    cyl.apply_translation([0, 0, height / 2])
    direction = vec / height
    z_axis = np.array([0, 0, 1])
    rotation, _ = trimesh.geometry.align_vectors(z_axis, direction, return_angle=True)
    cyl.apply_transform(rotation)
    cyl.apply_translation(p1)
    return cyl

# Gabungkan semua segmen rangka
frame = [create_cylinder_between(spline_points[i], spline_points[i+1]) for i in range(len(spline_points)-1)]
frame_mesh = trimesh.util.concatenate(frame)

# Buat roda (torus)
def create_wheel(center):
    wheel = trimesh.creation.torus(radius=0.4, tube_radius=0.05)
    wheel.apply_translation(center)
    return wheel

rear_wheel = create_wheel([-0.5, 0.0, 0.0])
front_wheel = create_wheel([0.6, 0.2, 0.0])

# Buat sadel (squashed sphere)
saddle = trimesh.creation.icosphere(subdivisions=3, radius=0.1)
saddle.apply_translation([0.0, 0.45, 0.0])
saddle.apply_scale([1.5, 0.5, 1.0])

# Gabungkan semua mesh
sepeda = trimesh.util.concatenate([frame_mesh, rear_wheel, front_wheel, saddle])

# Simpan ke file .obj
sepeda.export('sepeda_spline.obj')
print("Model berhasil diekspor ke sepeda_spline.obj")
