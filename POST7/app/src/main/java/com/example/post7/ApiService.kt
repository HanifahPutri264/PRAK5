package com.example.post7


interface ApiService {
    @GET ("en/books")
    fun getBooks(): Call<List<Book>>
}

Book
package com.prak.prak7_309

data class Book(
    val title: String?,
    val releaseDate: String?
)

BookAdapter
package com.prak.prak7_309

import android.view.LayoutInflater
import android.view.ViewGroup
import androidx.recyclerview.widget.RecyclerView
import com.prak.prak7_309.databinding.ItemBookBinding


class BookAdapter(private var list: List<Book>) : RecyclerView.Adapter<BookAdapter.ViewHolder>() {

    inner class ViewHolder(val binding: ItemBookBinding)
        : RecyclerView.ViewHolder(binding.root) {

        fun bind(book: Book) {
            binding.tvCardTitle.text = book.title
            binding.tvCardDate.text = book.releaseDate
        }

    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val binding = ItemBookBinding.inflate(
            LayoutInflater.from(parent.context),
            parent,
            false
        )
        return ViewHolder(binding)
    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        holder.bind(list[position])
    }

    override fun getItemCount(): Int = list.size
}