using UnityEngine;
using System;
using System.Runtime.InteropServices;

public class StartScript : MonoBehaviour {
    [DllImport("turing")]
    private static extern IntPtr init();
    [DllImport("turing")]
    private static extern void run(IntPtr tm, byte[] buf);
    [DllImport("turing")]
    private static extern void safeIterate(IntPtr tm, byte[] buf);

    void Start () {
        //var t = init();
        //byte[] buf = new byte[300];
        //run(t, buf);
        //Debug.Log(System.Text.Encoding.ASCII.GetString(buf));
    }
}
