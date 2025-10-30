import bpy

# Hapus semua objek yang ada dulu
bpy.ops.object.select_all(action='SELECT')
bpy.ops.object.delete(use_global=False)

# Tambah curve Bezier
bpy.ops.curve.primitive_bezier_curve_add(location=(0, 0, 0))
curve = bpy.context.object
curve.name = "RangkaSepeda"

# Masuk edit mode untuk atur titik kontrol spline
bpy.ops.object.mode_set(mode='EDIT')

# Ambil spline dan titiknya
spline = curve.data.splines[0]
points = spline.bezier_points

# Atur posisi titik agar berbentuk rangka sederhana
points[0].co = (-0.8, 0, 0.3)
points[0].handle_left_type = 'AUTO'
points[0].handle_right_type = 'AUTO'

points[1].co = (0.8, 0, 0.2)
points[1].handle_left_type = 'AUTO'
points[1].handle_right_type = 'AUTO'

# Tambah titik spline baru agar rangka lebih kompleks
spline.bezier_points.add(count=2)
points = spline.bezier_points

points[2].co = (0.3, 0, 0.8)
points[2].handle_left_type = 'AUTO'
points[2].handle_right_type = 'AUTO'

points[3].co = (-0.3, 0, 0.5)
points[3].handle_left_type = 'AUTO'
points[3].handle_right_type = 'AUTO'

# Kembali ke object mode
bpy.ops.object.mode_set(mode='OBJECT')

# Atur bevel agar spline jadi tabung (rangka tebal)
curve.data.bevel_depth = 0.02
curve.data.bevel_resolution = 5

# Smooth shading agar mulus
bpy.ops.object.shade_smooth()
