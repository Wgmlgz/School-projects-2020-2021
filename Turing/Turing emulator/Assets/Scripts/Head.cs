using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Head : MonoBehaviour {
    [HideInInspector] public TuringMachineGO tm;

    public int old_x = 0;
    public int cur_x = 0;
    public float cur_time;
    public float move_time = 1;

    public TMPro.TextMeshProUGUI state_t;

    public void setState(int state) {
        state_t.SetText(state.ToString());
    }
    public void moveTo(int x) {
        if (x == cur_x) return;
        if (Mathf.RoundToInt(Mathf.Abs(x - cur_x)) > 1) {
            old_x = x;
            cur_x = x;
            return;
        }
        cur_time = 0;
        old_x = cur_x;
        cur_x = x;
    }
    public void moveLeft() {
        moveTo(cur_x - 1);
    }
    public void moveRight() {
        moveTo(cur_x + 1);
    }
    private void Update() {
        cur_time += Time.deltaTime;
        transform.position = Vector3.Lerp(tm.getPos(old_x), tm.getPos(cur_x), cur_time / move_time);
    }
}
