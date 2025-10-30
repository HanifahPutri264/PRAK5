# Tambah crank (penghubung pedal)
bpy.ops.mesh.primitive_cylinder_add(
    radius=0.03, 
    depth=0.3, 
    location=(1.6, -0.3, -0.4), 
    rotation=(0, math.radians(90), 0)
)
crank = bpy.context.active_object
crank.name = "Crank"
crank.data.materials.append(mat)
