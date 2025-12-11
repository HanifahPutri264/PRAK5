package com.example.prakpmob8

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView

class TaskAdapter(
    private val tasks: MutableList<Task>,
    private val onDelete: (Int) -> Unit
) : RecyclerView.Adapter<TaskAdapter.TaskViewHolder>() {

    inner class TaskViewHolder(item: View) : RecyclerView.ViewHolder(item) {
        val title = item.findViewById<TextView>(R.id.tvTaskTitle)
        val desc = item.findViewById<TextView>(R.id.tvTaskDesc)
        val deadline = item.findViewById<TextView>(R.id.tvTaskDeadline)
        val delete = item.findViewById<ImageView>(R.id.btnDelete)
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): TaskViewHolder {
        val view = LayoutInflater.from(parent.context)
            .inflate(R.layout.item_task, parent, false)
        return TaskViewHolder(view)
    }

    override fun onBindViewHolder(holder: TaskViewHolder, position: Int) {
        val t = tasks[position]
        holder.title.text = t.title
        holder.desc.text = t.description
        holder.deadline.text = t.deadline

        holder.delete.setOnClickListener {
            onDelete(position)
        }
    }

    override fun getItemCount() = tasks.size
}
