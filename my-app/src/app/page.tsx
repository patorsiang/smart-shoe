import {
  Container,
  CssBaseline,
  Grid2 as Grid,
  AppBar,
  Toolbar,
  Typography,
} from "@mui/material";
import DirectionsRunIcon from "@mui/icons-material/DirectionsRun";
import BLEConnectPaper from "@/components/BLEConnectPaper";

export default function Home() {
  return (
    <>
      <AppBar position="static">
        <Container maxWidth="xl">
          <Toolbar disableGutters>
            <DirectionsRunIcon sx={{ display: "flex", mr: 1 }} />
            <Typography variant="h6" component="div" sx={{ flexGrow: 1 }}>
              Smart Shoe Demo
            </Typography>
          </Toolbar>
        </Container>
      </AppBar>
      <CssBaseline />
      <Container fixed>
        <Grid container spacing={1} sx={{ padding: "1em" }}>
          <Grid size={12}>
            <BLEConnectPaper />
          </Grid>
          {/* <Grid size={6}>
            <BLEConnectPaper />
          </Grid>
          <Grid size={6}>
            <BLEConnectPaper />
          </Grid> */}
        </Grid>
      </Container>
    </>
  );
}
