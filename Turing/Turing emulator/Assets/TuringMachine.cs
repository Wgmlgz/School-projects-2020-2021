using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;


public class TuringMachine : MonoBehaviour
{
    [DllImport("turing.h")]
    private static extern int[,] fillArray(int size);
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
