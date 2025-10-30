import com.example.post4.Warga

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.example.post4.R

class WargaAdapter : RecyclerView.Adapter<WargaAdapter.WargaViewHolder>() {

    private var wargaList: List<Warga> = emptyList()

    inner class WargaViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {
        val tvNama: TextView = itemView.findViewById(R.id.tvNama)
        val tvNik: TextView = itemView.findViewById(R.id.tvNik)
        val tvAlamat: TextView = itemView.findViewById(R.id.tvAlamat)
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): WargaViewHolder {
        val view = LayoutInflater.from(parent.context)
            .inflate(R.layout.item_warga, parent, false)
        return WargaViewHolder(view)
    }

    override fun onBindViewHolder(holder: WargaViewHolder, position: Int) {
        val warga = wargaList[position]
        holder.tvNama.text = warga.nama
        holder.tvNik.text = warga.nik
        holder.tvAlamat.text = "${warga.desa}, RT ${warga.rt}/RW ${warga.rw}"
    }

    override fun getItemCount(): Int = wargaList.size

    fun submitList(data: List<Warga>) {
        wargaList = data
        notifyDataSetChanged()
    }
}
