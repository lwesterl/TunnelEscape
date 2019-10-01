package games.tunnelescape.tunnelescape;

import android.support.test.runner.AndroidJUnit4;
import org.junit.Test;
import org.junit.runner.RunWith;
import static org.junit.Assert.*;

@RunWith(AndroidJUnit4.class)
public class PhysicsPropertiesInstrumentedTest {

    // notice we are testing C++ components so physics-lib must be loaded
    static
    {
        System.loadLibrary("physics-lib");
    }

    @Test
    public void setGravityX() {
        PhysicsProperties.setGravityX(50.f);
        assertEquals(50.f, PhysicsProperties.getGravityX(), 0.001f);
    }

    @Test
    public void setGravityY() {
        PhysicsProperties.setGravityY(1000.f);
        assertEquals(1000.f, PhysicsProperties.getGravityY(), 0.001f);
        PhysicsProperties.setGravityY(10.f);
        assertEquals(10.f, PhysicsProperties.getGravityY(), 0.001f);
    }

    @Test
    public void setPosition() {
        PhysicsProperties physics = new PhysicsProperties();
        physics.setPosition(new Vector2f(100.f, 500.f));
        assertEquals(100.f, physics.getPosition().getX(), 0.001f);
        assertEquals(500.f, physics.getPosition().getY(), 0.001f);
    }

    @Test
    public void setVelocity() {
        PhysicsProperties physics = new PhysicsProperties();
        physics.setVelocity(new Vector2f(100.f, 5.f));
        assertEquals(100.f, physics.getVelocity().getX(), 0.001f);
        assertEquals(5.f, physics.getVelocity().getY(), 0.001f);
    }

    @Test
    public void setOrigin_transform() {
        PhysicsProperties physics = new PhysicsProperties();
        physics.setOrigin_transform(new Vector2f(20.f, 15.f));
        assertEquals(20.f, physics.getOrigin_transform().getX(), 0.001f);
        assertEquals(15.f, physics.getOrigin_transform().getY(), 0.001f);
    }
}