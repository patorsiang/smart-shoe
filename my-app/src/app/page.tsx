import {
  Container,
  CssBaseline,
  Grid2 as Grid,
  AppBar,
  Toolbar,
  Typography,
  Stack,
} from "@mui/material";
import DirectionsRunIcon from "@mui/icons-material/DirectionsRun";
import BLEConnectButton from "@/components/BLEConnectButton";
import { BLEProvider } from "@/components/contexts/BLEContext";
import Battery from "@/components/Battery";
import AlertMessage from "@/components/AlertMessage";
import WifiStatus from "@/components/WifiStatus";
import FootHeatMap from "@/components/FootHeatMap";
import MPUPaper from "@/components/MPUPaper";
import CountStep from "@/components/CountStep";
import ResetButton from "@/components/ResetButton";

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
            <Stack
              direction="row"
              sx={{
                justifyContent: "flex-end",
                alignItems: "center",
              }}
            >
              <Battery />
              <ResetButton />
            </Stack>
          </Grid>
          <Grid size={12}>
            <AlertMessage />
          </Grid>
          <Grid size={{ md: 6, xs: 12 }}>
            <FootHeatMap />
          </Grid>
          <Grid size={{ md: 6, xs: 12 }}>
            <CountStep />
          </Grid>
          <Grid size={{ md: 6, xs: 12 }}>
            <MPUPaper />
          </Grid>
        </Grid>
      </Container>
    </BLEProvider>
  );
}
