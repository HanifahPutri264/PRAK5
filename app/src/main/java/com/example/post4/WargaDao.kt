package com.example.post4

import androidx.room.*

@Dao
interface WargaDao {

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertWarga(warga: Warga)

    @Query("SELECT * FROM tabel_warga")
    suspend fun getAllWarga(): List<Warga>

    @Query("DELETE FROM tabel_warga")
    suspend fun deleteAll()
}
