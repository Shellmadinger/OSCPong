using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OSCPaddle : MonoBehaviour
{
    public float speed;
    public Rigidbody2D ball;
    public Rigidbody2D OSCPad;
    // Start is called before the first frame update

    // Update is called once per frame
    void FixedUpdate()
    {
        if (ball.transform.position.x > 0f)
        {

            if (this.ball.position.y > this.transform.position.y)
            {
                OSCPad.AddForce(Vector3.up * speed);
            }

            else if (this.ball.position.y < this.transform.position.y)
            {
                OSCPad.AddForce(Vector3.down * speed);
            }
        }

        else
        {
            OSCPad.velocity *= 0;
        }
    }
}
