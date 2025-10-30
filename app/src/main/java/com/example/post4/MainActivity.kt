package com.example.post4

import android.os.Bundle
import android.widget.*
import androidx.appcompat.app.AppCompatActivity
import androidx.lifecycle.lifecycleScope
import kotlinx.coroutines.launch

class MainActivity : AppCompatActivity() {

    private lateinit var etNama: EditText
    private lateinit var etNIK: EditText
    private lateinit var etKabupaten: EditText
    private lateinit var etKecamatan: EditText
    private lateinit var etDesa: EditText
    private lateinit var etRT: EditText
    private lateinit var etRW: EditText
    private lateinit var rgGender: RadioGroup
    private lateinit var spStatus: Spinner
    private lateinit var btnSimpan: Button
    private lateinit var btnReset: Button
    private lateinit var tvOutput: TextView

    private var gender = ""
    private lateinit var database: DatabaseWarga

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Inisialisasi view
        etNama = findViewById(R.id.etNama)
        etNIK = findViewById(R.id.etNIK)
        etKabupaten = findViewById(R.id.etKabupaten)
        etKecamatan = findViewById(R.id.etKecamatan)
        etDesa = findViewById(R.id.etDesa)
        etRT = findViewById(R.id.etRT)
        etRW = findViewById(R.id.etRW)
        rgGender = findViewById(R.id.rgGender)
        spStatus = findViewById(R.id.spStatus)
        btnSimpan = findViewById(R.id.btnSimpan)
        btnReset = findViewById(R.id.btnReset)
        tvOutput = findViewById(R.id.tvOutput)

        // Inisialisasi database
        database = DatabaseWarga.getDatabase(this)

        // Spinner: Status Pernikahan
        val statusList = arrayOf("Belum Menikah", "Menikah")
        val adapter = ArrayAdapter(this, android.R.layout.simple_spinner_dropdown_item, statusList)
        spStatus.adapter = adapter

        // RadioGroup Jenis Kelamin
        rgGender.setOnCheckedChangeListener { _, checkedId ->
            gender = when (checkedId) {
                R.id.rbLaki -> "Laki-Laki"
                R.id.rbPerempuan -> "Perempuan"
                else -> ""
            }
        }

        // Tombol Simpan
        btnSimpan.setOnClickListener {
            val warga = Warga(
                nama = etNama.text.toString(),
                nik = etNIK.text.toString(),
                kabupaten = etKabupaten.text.toString(),
                kecamatan = etKecamatan.text.toString(),
                desa = etDesa.text.toString(),
                rt = etRT.text.toString(),
                rw = etRW.text.toString(),
                gender = gender,
                status = spStatus.selectedItem.toString()
            )

            lifecycleScope.launch {
                database.wargaDao().insertWarga(warga)
                tampilkanData()
            }
        }

        // Tombol Reset
        btnReset.setOnClickListener {
            lifecycleScope.launch {
                database.wargaDao().deleteAll()
                tampilkanData()
            }
        }

        tampilkanData() // tampilkan data saat aplikasi dibuka
    }

    private fun tampilkanData() {
        lifecycleScope.launch {
            val daftarWarga = database.wargaDao().getAllWarga()
            if (daftarWarga.isEmpty()) {
                tvOutput.text = "Daftar Warga Negara:"
            } else {
                val hasil = daftarWarga.mapIndexed { index, warga ->
                    "${index + 1}. ${warga.nama} (${warga.gender}) - ${warga.status}\n" +
                            "NIK: ${warga.nik}\n" +
                            "Alamat: RT ${warga.rt}/RW ${warga.rw}, ${warga.desa}, ${warga.kecamatan}, ${warga.kabupaten}"
                }.joinToString("\n\n")

                tvOutput.text = "Daftar Warga Negara:\n$hasil"
            }
        }
    }
}
