/**
 * @file ApiStatus.java
 * @author Lauri Westerholm
 * @details Contains ApiStatus: constants for API return values
 */

package games.tunnelescape.tunnelescape.resources;


import android.support.annotation.IntDef;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

/**
 * @class ApiStatus
 * Contains int codes for different api return status values
 */
public class ApiStatus {
    @Retention(RetentionPolicy.SOURCE)
    @IntDef ({Ok, Error, UserExists})
    public @interface ApiStatusRef {}

    public static final int Ok = 0;
    public static final int Error = 1;
    public static final int UserExists = 2;

    public final int status;

    /**
     * Validate int value
     * @param apiStatus constant int value for ApiStatus
     */
    public ApiStatus(@ApiStatusRef int apiStatus) { this.status = apiStatus; }
}
