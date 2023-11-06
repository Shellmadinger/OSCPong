using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PaddleMovementPlayer : MonoBehaviour
{
    public float speed;
    float vertPaddleMov;
    
    // Update is called once per frame
    void Update()
    {
        Move();
    }

    void Move()
    {
        vertPaddleMov = Input.GetAxis("Vertical");
        transform.Translate(Vector3.up * vertPaddleMov * speed * Time.deltaTime);
    }
}
