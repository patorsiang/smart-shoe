import { Typography } from "@mui/material";

import { Props } from "@/components/types";

import { Item } from "./StyledComponents";

export default function ItemPaperTemplate({
  children,
  title,
}: Props & { title: string }) {
  return (
    <Item elevation={4}>
      <Typography variant="h6" component="h6">
        {title}
      </Typography>
      {children}
    </Item>
  );
}
