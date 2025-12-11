package com.example.prakpmob8

import android.app.DatePickerDialog
import android.content.Context
import android.graphics.Color
import android.graphics.drawable.ColorDrawable
import android.view.LayoutInflater
import android.widget.Toast
import com.example.prakpmob8.databinding.UploadDialogBinding
import com.google.android.material.dialog.MaterialAlertDialogBuilder
import java.text.SimpleDateFormat
import java.util.Calendar
import java.util.Locale

class AddBookDialog(
    private val context: Context,
    private val onSave: (String, String, String) -> Unit // title, desc, deadline
) {

    private val binding: UploadDialogBinding =
        UploadDialogBinding.inflate(LayoutInflater.from(context))

    fun show() {
        val dialog = MaterialAlertDialogBuilder(context)
            .setView(binding.root)
            .setCancelable(true)
            .create()

        dialog.window?.setBackgroundDrawable(ColorDrawable(Color.TRANSPARENT))

        // DATE PICKER
        binding.editTextDeadline.setOnClickListener {
            val c = Calendar.getInstance()
            val dp = DatePickerDialog(
                context,
                { _, y, m, d ->
                    val cal = Calendar.getInstance()
                    cal.set(y, m, d)
                    val df = SimpleDateFormat("dd/MM/yyyy", Locale.getDefault())
                    binding.editTextDeadline.setText(df.format(cal.time))
                },
                c.get(Calendar.YEAR),
                c.get(Calendar.MONTH),
                c.get(Calendar.DAY_OF_MONTH)
            )
            dp.show()
        }

        dialog.show()
    }
}
