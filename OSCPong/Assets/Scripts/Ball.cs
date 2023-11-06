using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Ball : MonoBehaviour
{
    public Rigidbody2D ballBody;
    public float speed;
    int ballTrajectoryX;
    int ballTrajectoryY;
    // Start is called before the first frame update
    void Start()
    {
        InitalForce();
    }

    public void InitalForce()
    {
        ballTrajectoryX = Random.Range(0, 2) == 0 ? -1 : 1;
        ballTrajectoryY = Random.Range(0, 2) == 0 ? -1 : 1;

        ballBody.velocity = new Vector2(ballTrajectoryX * speed, ballTrajectoryY * speed);
        Debug.Log(ballBody.velocity);
    }
}
