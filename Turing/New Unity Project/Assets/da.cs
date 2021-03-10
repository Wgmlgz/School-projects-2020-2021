using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class da : MonoBehaviour
{
    public Transform target;
    public float start_force = 100;
    public float y_force = 100;
    bool f = false;

    // Start is called before the first frame update
    void Start()
    {
        Vector3 force = new Vector3(0, 0, start_force);
        transform.LookAt(target);
        GetComponent<Rigidbody>().AddRelativeForce(force);

       
    }

    // Update is called once per frame
    void Update()
    {
        if (f == false) {
            f = true;
            var vel = GetComponent<Rigidbody>().velocity;
            float t = target.position.z / vel.z;
            Debug.Log(t);
            GetComponent<Rigidbody>().velocity = new Vector3(vel.x, vel.y + 10f * t, vel.z);
            //GetComponent<Rigidbody>().AddForce(new Vector3(0, 10 * t, 0));
        }
    }
}
