/**
 * @file RegisterDialogFragment.java
 * @author Lauri Westerholm
 * Contains RegisterDialogFragment used to create a new user
 */

package games.tunnelescape.UI;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.support.v4.app.DialogFragment;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.Toast;

import games.tunnelescape.R;
import games.tunnelescape.tunnelescape.resources.ApiStatus;
import games.tunnelescape.tunnelescape.resources.ScoreServerHandler;

import java.util.concurrent.Callable;

/**
 * @class RegisterDialogFragment
 * Create AlertDialog fragment which asks username to be registered
 */
public class RegisterDialogFragment extends DialogFragment {

    private String username;

    /**
     * onCreateDialog override
     * @param savedInstanceState state of the activity
     * @return a new Dialog used for registering an user
     */
    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
        LayoutInflater inflater = requireActivity().getLayoutInflater();
        // set custom layout for AlertDialog
        builder .setView(inflater.inflate(R.layout.user_register_layout, null))
        // create buttons
                .setPositiveButton(R.string.user_register_button, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {}
                })
                .setNegativeButton(R.string.skip_registration_button, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {}
                });

        return builder.create();
    }

    /**
     * onStart override
     * Create a dialog for registering a new user
     */
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
                    username = nameEdit.getText().toString();
                    ProgressBar registerProgress = dialog.getWindow().findViewById(R.id.registerProgress);
                    registerProgress.setVisibility(View.VISIBLE);
                    try {
                        ScoreServerHandler.createUser(username, new Callable<Void>() {
                            @Override
                            public Void call() {
                                @ApiStatus.ApiStatusRef int status = ScoreServerHandler.getApiStatus();
                                if (status == ApiStatus.UserExists) {
                                   TextView errorTextView = dialog.getWindow().findViewById(R.id.errorTextView);
                                   errorTextView.setVisibility(View.VISIBLE);
                                   registerProgress.setVisibility(View.INVISIBLE);
                                   return null;
                                } else if (status == ApiStatus.Error) {
                                    Toast toast = Toast.makeText(getContext(), "Error\nTry Stats to create an user later on", Toast.LENGTH_LONG);
                                    toast.show();
                                } else if (status == ApiStatus.Ok) {
                                    ScoreServerHandler.saveUser(getContext(), username, ScoreServerHandler.UserID);
                                    String text = username + " successfully created";
                                    Toast toast = Toast.makeText(getContext(), text, Toast.LENGTH_SHORT);
                                    toast.show();
                                }
                                registerProgress.setVisibility(View.INVISIBLE);
                                dialog.dismiss();
                                return null;
                            }
                        });
                    } catch (Exception e) {
                        e.printStackTrace();
                    }

                }

            });
            Button negativeButton = dialog.getButton(Dialog.BUTTON_NEGATIVE);
            negativeButton.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    ScoreServerHandler.saveUser(getContext(), "", "-1");
                    dismiss();
                }
            });
        }
    }

}
