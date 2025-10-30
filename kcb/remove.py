from rembg import remove
from PIL import Image

def hapus_background(input_file, output_file):
    try:
        with open(input_file, 'rb') as file_input:
            input_data = file_input.read()

        output_data = remove(input_data)

        with open(output_file, 'wb') as file_output:
            file_output.write(output_data)

        print(f" Background berhasil dihapus! Gambar disimpan di: {output_file}")
    except Exception as e:
        print(f" Terjadi kesalahan: {e}")


if __name__ == "__main__":
    input_gambar = "sunset.jpeg"
    output_gambar = "pp 1 remove.jpg"

    hapus_background(input_gambar, output_gambar)