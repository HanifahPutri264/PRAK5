package com.example.prakpmob8

import android.app.AlertDialog
import android.app.DatePickerDialog
import android.os.Bundle
import android.view.View
import android.widget.EditText
import android.widget.LinearLayout
import androidx.appcompat.app.AppCompatActivity
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.prakpmob8.databinding.ActivityMainBinding
import java.util.Calendar

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding
    private lateinit var adapter: TaskAdapter
    private val tasks = mutableListOf<Task>()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // RecyclerView setup
        adapter = TaskAdapter(tasks) { position ->
            tasks.removeAt(position)
            adapter.notifyDataSetChanged()
            checkEmpty()
        }

        binding.rvTasks.adapter = adapter
        binding.rvTasks.layoutManager = LinearLayoutManager(this)

        // FAB klik untuk tambah task
        binding.fabAddTask.setOnClickListener {
            showAddDialog()
        }

        checkEmpty()
    }

    // ---------------------------
    // KONTROL EMPTY / LIST
    // ---------------------------
    private fun checkEmpty() {
        if (tasks.isEmpty()) {
            binding.layoutEmpty.visibility = View.VISIBLE
            binding.rvTasks.visibility = View.GONE
        } else {
            binding.layoutEmpty.visibility = View.GONE
            binding.rvTasks.visibility = View.VISIBLE
        }
    }

    // ---------------------------
    // POPUP TAMBAH TUGAS
    // ---------------------------
    private fun showAddDialog() {
        val dialogView = layoutInflater.inflate(R.layout.upload_dialog, null)

        val title = dialogView.findViewById<EditText>(R.id.editTextTaskTitle)
        val desc = dialogView.findViewById<EditText>(R.id.editTextTaskDesc)
        val deadline = dialogView.findViewById<EditText>(R.id.editTextDeadline)

        // DATE PICKER
        deadline.setOnClickListener {
            val cal = Calendar.getInstance()

            DatePickerDialog(
                this,
                { _, y, m, d ->
                    deadline.setText("$d-${m + 1}-$y")
                },
                cal.get(Calendar.YEAR),
                cal.get(Calendar.MONTH),
                cal.get(Calendar.DAY_OF_MONTH)
            ).show()
        }

        // SHOW DIALOG
        AlertDialog.Builder(this)
            .setTitle("Tambah Tugas")
            .setView(dialogView)
            .setPositiveButton("Tambah") { _, _ ->
                tasks.add(
                    Task(
                        title.text.toString(),
                        desc.text.toString(),
                        deadline.text.toString()
                    )
                )
                adapter.notifyDataSetChanged()
                checkEmpty()
            }
            .setNegativeButton("Batal", null)
            .show()
    }
}
