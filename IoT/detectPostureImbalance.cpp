#include "detectPostureImbalance.h"
#include "global_params.h"

int badPostureCount = 0;

void detectPostureImbalance()
{
  Serial.println("Checking your posture...");
  float total = (float)getTotalForce();
  // Calculate percentage contribution
  float frontPct = ((double)getForce(0) / total);
  float midPct = ((double)getForce(1) / total);
  float heelPct = ((double)getForce(2) / total);

  // Define acceptable ranges
  const float minFront = 0.25, maxFront = 0.5;
  const float minMid = 0.15, maxMid = 0.4;
  const float minHeel = 0.25, maxHeel = 0.5;

  bool unbalanced =
      (frontPct < minFront || frontPct > maxFront) ||
      (midPct < minMid || midPct > maxMid) ||
      (heelPct < minHeel || heelPct > maxHeel);

  if (unbalanced)
  {
    badPostureCount++;
  }
  else
  {
    badPostureCount = 0;
  }

  if (badPostureCount >= BAD_POSTURE_DETECTION_NUM)
  {
    Serial.println("⚠️ Warning: Unbalanced posture detected!");
    Serial.print("Front: ");
    Serial.print(frontPct);
    Serial.print("%, ");
    Serial.print("Mid: ");
    Serial.print(midPct);
    Serial.print("%, ");
    Serial.print("Heel: ");
    Serial.print(heelPct);
    Serial.println("%");

    readingsJSONInfo["title"] = "⚠️ Warning: Unbalanced posture detected!";
    readingsJSONInfo["msg"] = "Front: " + String(frontPct) + "%, Mid: " + String(midPct) + "%, Heel: " + String(heelPct) + "%";
    readingsJSONInfo["type"] = "warning";

    upload("uok/iot/nt375/smart_shoe/info", JSON.stringify(readingsJSONInfo), 0, 0);
  }
}
