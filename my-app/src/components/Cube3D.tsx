"use client";

import { useEffect, useRef, useState } from "react";
import { Box } from "@mui/material";
import * as THREE from "three";

function parentWidth(elem: HTMLDivElement | null) {
  const clientWidth = elem?.parentElement?.clientWidth;
  return clientWidth ? clientWidth - 15 : 0;
}

function parentHeight(elem: HTMLDivElement | null) {
  const clientHeight = elem?.parentElement?.clientHeight;
  return clientHeight ? clientHeight : 0;
}

export default function Cube3D({ gyro }: { gyro: Record<string, number> }) {
  const [cube, setCube] =
    useState<
      THREE.Mesh<
        THREE.BoxGeometry,
        THREE.MeshBasicMaterial[],
        THREE.Object3DEventMap
      >
    >();
  const ref = useRef<HTMLDivElement>(null);

  useEffect(() => {
    const container = ref.current;
    if (!container) return;

    const scene = new THREE.Scene();
    scene.background = new THREE.Color(0xffffff);

    const camera = new THREE.PerspectiveCamera(
      75,
      parentWidth(container) / parentHeight(container),
      0.1,
      1000
    );
    const renderer = new THREE.WebGLRenderer({ antialias: true });

    renderer.setSize(parentWidth(container), parentHeight(container));
    container.appendChild(renderer.domElement);

    const geometry = new THREE.BoxGeometry(5, 1, 4);
    const cubeMaterials = [
      new THREE.MeshBasicMaterial({ color: 0x03045e }),
      new THREE.MeshBasicMaterial({ color: 0x023e8a }),
      new THREE.MeshBasicMaterial({ color: 0x0077b6 }),
      new THREE.MeshBasicMaterial({ color: 0x03045e }),
      new THREE.MeshBasicMaterial({ color: 0x023e8a }),
      new THREE.MeshBasicMaterial({ color: 0x0077b6 }),
    ];
    const newCube = new THREE.Mesh(geometry, cubeMaterials);
    setCube(newCube);
    scene.add(newCube);
    camera.position.z = 5;

    const onWindowResize = () => {
      camera.aspect = parentWidth(container) / parentHeight(container);
      camera.updateProjectionMatrix();
      renderer.setSize(parentWidth(container), parentHeight(container));
    };

    window.addEventListener("resize", onWindowResize, false);

    const animate = () => {
      renderer.render(scene, camera);
      requestAnimationFrame(animate);
    };
    animate();

    return () => {
      window.removeEventListener("resize", onWindowResize);
      if (container && renderer.domElement.parentNode === container) {
        container.removeChild(renderer.domElement);
      }
    };
  }, []);

  useEffect(() => {
    if (cube && gyro) {
      cube.rotation.x = gyro?.["y"] ?? 0;
      cube.rotation.z = gyro?.["x"] ?? 0;
      cube.rotation.y = gyro?.["z"] ?? 0;
    }
  }, [cube, gyro]);

  return <Box ref={ref}></Box>;
}
