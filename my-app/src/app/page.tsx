import {
  Container,
  CssBaseline,
  Grid2 as Grid,
  AppBar,
  Toolbar,
  Typography,
} from "@mui/material";
import DirectionsRunIcon from "@mui/icons-material/DirectionsRun";
import BLEConnectButton from "@/components/BLEConnectButton";
import { BLEProvider } from "@/components/contexts/BLEContext";
import Battery from "@/components/Battery";
import WelcomeAlert from "@/components/AlertMessage";
import WifiStatus from "@/components/WifiStatus";
import FootHeatMap from "@/components/FootHeatMap";

export default function Home() {
  return (
    <BLEProvider>
      <AppBar position="static">
        <Container maxWidth="xl">
          <Toolbar disableGutters>
            <DirectionsRunIcon sx={{ display: "flex", mr: 1 }} />
            <Typography variant="h6" component="div" sx={{ flexGrow: 1 }}>
              Smart Shoe Demo
            </Typography>
            <BLEConnectButton />
            <WifiStatus />
          </Toolbar>
        </Container>
      </AppBar>
      <CssBaseline />
      <Container fixed>
        <Grid container spacing={4} sx={{ padding: "1em" }}>
          <Grid size={12}>
            <Battery />
          </Grid>
          <Grid size={12}>
            <WelcomeAlert />
          </Grid>
          <Grid size={{ md: 6, xs: 12 }}>
            <FootHeatMap />
          </Grid>
          {/* <Grid size={{ md: 6, xs: 12 }}>
            <FootHeatMap />
          </Grid>*/}
        </Grid>
      </Container>
    </BLEProvider>
  );
}
