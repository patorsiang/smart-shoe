import { useState } from "react";
import { Svg, Circle, Path } from "react-native-svg";

type Props = {
  disabled?: boolean;
};

export default function InsoleHeatMap(props: Props) {
  const { disabled } = props;
  const disableColor = "#B2BEB5";
  const [color, setColor] = useState({ fore: "", mid: "", heel: "" });

  return (
    <Svg width={200} height={450} viewBox="0 0 200 400">
      {/* Forefoot (top part of insole) */}
      <Circle
        cx="100"
        cy="50"
        r="40"
        fill={props.disabled ? disableColor : color.fore}
      />

      {/* Midfoot (middle part of insole) */}
      <Circle
        cx="100"
        cy="150"
        r="30"
        fill={props.disabled ? disableColor : color.mid}
      />

      {/* Heel (bottom part of insole) */}
      <Circle
        cx="100"
        cy="300"
        r="50"
        fill={props.disabled ? disableColor : color.heel}
      />

      {/* Outline of the insole */}
      <Path
        d="M50,10 C70,-10 130,-10 150,10 C180,50 180,250 150,370 C130,400 70,400 50,370 C20,250 20,50 50,10 Z"
        stroke={disabled ? disableColor : "black"}
        strokeWidth="3"
        fill="none"
      />
    </Svg>
  );
}
