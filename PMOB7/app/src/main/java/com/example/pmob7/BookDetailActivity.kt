package com.example.pmob7

import android.os.Bundle
import android.widget.ImageView
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import com.bumptech.glide.Glide
import com.example.pmob7.databinding.ActivityBookDetailBinding

class BookDetailActivity : AppCompatActivity() {

    private lateinit var binding: ActivityBookDetailBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityBookDetailBinding.inflate(layoutInflater)
        setContentView(binding.root)

        val title = intent.getStringExtra("title")
        val cover = intent.getStringExtra("cover")
        val date = intent.getStringExtra("date")
        val summary = intent.getStringExtra("summary")

        binding.tvTitle.text = title
        binding.tvDate.text = date
        binding.tvSummary.text = summary

        Glide.with(this)
            .load(cover)
            .into(binding.imgCover)
    }
}
