package com.westerholmgmail.v.lauri.UI;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.support.v4.app.DialogFragment;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import com.westerholmgmail.v.lauri.tunnelescape.R;

/**
 * @class RegisterDialogFragment
 * Create AlertDialog fragment which asks username to be registered
 */
public class RegisterDialogFragment extends DialogFragment {

    public static String Username = "";

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
        LayoutInflater inflater = requireActivity().getLayoutInflater();
        // set custom layout for AlertDialog
        builder .setView(inflater.inflate(R.layout.user_register_layout, null))
        // create buttons
                .setPositiveButton(R.string.user_register_button, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        // try to register user

                    }
                })
                .setNegativeButton(R.string.skip_registration_button, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        // skip user registration
                    }
                });

        return builder.create();
    }

    @Override
    public void onStart() {
        super.onStart();
        AlertDialog dialog = (AlertDialog) getDialog();
        if (dialog != null) {
            Button positiveButton = dialog.getButton(Dialog.BUTTON_POSITIVE);
            positiveButton.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    EditText nameEdit = getDialog().getWindow().findViewById(R.id.username);
                    RegisterDialogFragment.Username = nameEdit.getText().toString();
                    System.out.println("____________________________Username______: " + RegisterDialogFragment.Username);
                    // TODO test if username is ok and save it to a file
                    // close the dialog
                    dismiss();
                }

            });
            Button negativeButton = dialog.getButton(Dialog.BUTTON_NEGATIVE);
            negativeButton.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    // TODO save to the file that user doesn't want to create a user
                    // close the dialog
                    dismiss();
                }
            });
        }
    }
}
