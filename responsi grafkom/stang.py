import math

# Tambah stang (handlebar)
bpy.ops.mesh.primitive_cylinder_add(
    radius=0.05, 
    depth=0.8, 
    location=(0.1, 0.5, 0.2), 
    rotation=(0, 0, math.radians(90))
)
stang = bpy.context.active_object
stang.name = "Stang"
stang.data.materials.append(mat)
