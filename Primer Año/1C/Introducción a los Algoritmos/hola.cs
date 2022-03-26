using System;
using System.Collections.Generic;
using System.IO;
using GTA;
using GTA.Math;

namespace LSTransit
{
	// Token: 0x02000004 RID: 4
	public class Main : Script
	{
		// Token: 0x06000016 RID: 22 RVA: 0x000027A0 File Offset: 0x000009A0
		public Main()
		{
			this.Initializer();
			base.Tick += delegate(object o, EventArgs e)
			{
				this.MainProcess();
			};
		}

		// Token: 0x06000017 RID: 23 RVA: 0x000027C0 File Offset: 0x000009C0
		public void Initializer()
		{
			this.game_Bus = null;
			this.game_Navigation = null;
			this.game_RouteIndex = 0;
			this.game_CurrentStop = 0;
			this.game_Credits = false;
			this.game_Speech = false;
			this.game_RouteBlips = false;
			this.game_PositionFix = false;
			this.game_DisableScript = false;
			this.game_RouteRunning = false;
			this.game_RemovePassengers = false;
			this.game_PositionFixMessage = false;
			this.game_WarpTimer = new Timer(3000);
			this.game_UnwarpTimer = new Timer(15000);
			this.game_InfoBoardTimer = new Timer(8000);
			this.game_MissionBlips = new List<Blip>();
			this.game_RouteInfo = new List<RouteInfo>();
			this.game_RouteProcess = Main.GameProcess.None;
			this.setings_Speech = false;
			this.settings_Earnings = 150;
			this.settings_WarpSpeed = 15000;
			this.LoadSettings();
			this.game_InfoBoard = new InfoBoard();
			this.game_InfoBoard.SetupRouteInfo("000 : Off duty", "None", "None", "None");
			base.Tick += delegate(object o, EventArgs e)
			{
				this.game_InfoBoard.Draw();
			};
			this.CreateRoutes();
		}

		// Token: 0x06000018 RID: 24 RVA: 0x000028D4 File Offset: 0x00000AD4
		public void Deinitializer()
		{
			this.StopNavigation();
			this.ShowBusBlip(false);
			this.game_DisableScript = true;
			this.game_RouteProcess = Main.GameProcess.Off;
			foreach (Blip blip in this.game_MissionBlips)
			{
				blip.Remove();
			}
			foreach (RouteInfo routeInfo in this.game_RouteInfo)
			{
				routeInfo.RemoveRoute();
			}
			if (Gameplay.DoesCarExist(this.game_Bus))
			{
				this.game_Bus.Delete();
			}
			this.game_InfoBoard.Show(false);
			UI.ShowSubtitle("OFF", 5000);
		}

		// Token: 0x06000019 RID: 25 RVA: 0x000029B4 File Offset: 0x00000BB4
		public void MainProcess()
		{
			this.RouteProcess();
			if (this.game_DisableScript)
			{
				return;
			}
			switch (this.game_RouteProcess)
			{
			case Main.GameProcess.None:
				if (!this.game_RouteBlips)
				{
					this.ShowRouteBlips(true);
				}
				for (int i = 0; i < this.game_RouteInfo.Count; i++)
				{
					if (Gameplay.IsPlayerAt(this.game_RouteInfo[i].SpawnPosition, 150f))
					{
						this.game_RouteIndex = i;
						this.game_CurrentStop = 0;
						this.CreateBus(this.game_RouteInfo[i].SpawnPosition);
						this.game_RouteProcess = Main.GameProcess.Initialize;
					}
				}
				return;
			case Main.GameProcess.Initialize:
				if (!this.game_RouteBlips)
				{
					this.ShowRouteBlips(true);
				}
				if (!Gameplay.DoesCarExist(this.game_Bus))
				{
					this.game_RouteProcess = Main.GameProcess.None;
					return;
				}
				if (!Gameplay.IsPlayerAt(this.game_RouteInfo[this.game_RouteIndex].SpawnPosition, 150f))
				{
					this.DeleteBus();
					this.game_RouteProcess = Main.GameProcess.None;
				}
				if (Gameplay.Player.IsInVehicle(this.game_Bus))
				{
					this.game_RouteProcess = Main.GameProcess.StartRoute;
				}
				if (!this.game_Credits && Gameplay.IsPlayerAt(this.game_RouteInfo[this.game_RouteIndex].SpawnPosition, 30f))
				{
					UI.ShowSubtitle("~b~LSTransit ~w~mod by ~y~Mordecki~w~.", 8000);
					this.game_Credits = true;
					return;
				}
				break;
			case Main.GameProcess.StartRoute:
				this.LoadSettings();
				this.ShowRouteBlips(false);
				this.game_RouteRunning = true;
				this.game_RouteInfo[this.game_RouteIndex].SpawnRoute();
				Game.Player.IgnoredByEveryone = true;
				Game.Player.Character.CanBeDraggedOutOfVehicle = false;
				this.game_InfoBoard.SetupInfo(this.game_RouteInfo[this.game_RouteIndex].Name, "Route started, drive to the first stop.");
				this.game_InfoBoardTimer.Restart();
				this.game_InfoBoard.Show(true);
				this.StartNavigation(this.game_RouteInfo[this.game_RouteIndex].BusStops[this.game_CurrentStop].Position);
				this.game_RouteProcess = Main.GameProcess.DriveToBusStop;
				return;
			case Main.GameProcess.DriveToBusStop:
				if (this.game_InfoBoard.Enabled && this.game_InfoBoardTimer.Finished)
				{
					this.game_InfoBoard.Show(false);
				}
				if (Gameplay.IsVehicleAt(this.game_Bus, this.game_RouteInfo[this.game_RouteIndex].BusStops[this.game_CurrentStop].Position, 18f) && this.game_Bus.IsStopped)
				{
					this.OpenBusDoors();
					this.StopNavigation();
					this.game_InfoBoard.Show(false);
					if (this.game_CurrentStop == 0)
					{
						this.game_InfoBoard.SetupRouteInfo(this.game_RouteInfo[this.game_RouteIndex].Name, "Terminus", this.GetBusStopName(0), this.GetBusStopName(1));
					}
					else if (this.game_CurrentStop >= this.game_RouteInfo[this.game_RouteIndex].BusStops.Count - 1)
					{
						this.game_InfoBoard.SetupInfo(this.game_RouteInfo[this.game_RouteIndex].Name, "Route finished, drive back to parking.");
					}
					else
					{
						this.game_InfoBoard.SetupRouteInfo(this.game_RouteInfo[this.game_RouteIndex].Name, this.GetBusStopName(this.game_CurrentStop - 1), this.GetBusStopName(this.game_CurrentStop), this.GetBusStopName(this.game_CurrentStop + 1));
					}
					this.game_InfoBoard.Show(true);
					this.game_RouteInfo[this.game_RouteIndex].BusStops[this.game_CurrentStop].ClearPassengersAllTasks();
					this.game_RouteProcess = Main.GameProcess.DriveToBusStopDoorCheck;
					return;
				}
				break;
			case Main.GameProcess.DriveToBusStopDoorCheck:
				if (this.AreBusDoorsWideOpen())
				{
					this.game_Bus.FreezePosition = true;
					this.game_RouteProcess = Main.GameProcess.WarpPassengersAtStop;
					return;
				}
				break;
			case Main.GameProcess.WarpPassengersAtStop:
				this.KeepBusDoorsOpen();
				if (this.IsBusEmpty())
				{
					this.game_PositionFix = false;
					this.game_WarpTimer.Setup(2000);
					this.game_RouteProcess = Main.GameProcess.WaitForPassengersEnter;
					return;
				}
				this.game_RemovePassengers = true;
				this.game_UnwarpTimer.Setup(this.settings_WarpSpeed);
				if (this.game_CurrentStop == 0)
				{
					this.game_RouteInfo[this.game_RouteIndex].BusStops[0].UnwarpPassengersFromBus();
				}
				else
				{
					this.game_RouteInfo[this.game_RouteIndex].BusStops[this.game_CurrentStop - 1].UnwarpPassengersFromBus();
				}
				this.game_RouteProcess = Main.GameProcess.UnwarpPassengersAtStop;
				return;
			case Main.GameProcess.WaitForPassengersEnter:
				if (this.game_CurrentStop >= this.game_RouteInfo[this.game_RouteIndex].BusStops.Count - 1)
				{
					this.game_Bus.FreezePosition = false;
					this.StartNavigationParking(this.game_RouteInfo[this.game_RouteIndex].SpawnPosition);
					this.game_RouteProcess = Main.GameProcess.FinishRoute;
					this.game_InfoBoard.Show(false);
					this.CloseBusDoors();
					return;
				}
				this.KeepBusDoorsOpen();
				this.game_RouteInfo[this.game_RouteIndex].BusStops[this.game_CurrentStop].WarpPassengersIntoBus(this.game_Bus);
				if (this.setings_Speech && Gameplay.DoesPedExist(this.game_RouteInfo[this.game_RouteIndex].BusStops[this.game_CurrentStop].Passengers[0]) && !this.game_Speech && this.game_RouteInfo[this.game_RouteIndex].BusStops[this.game_CurrentStop].Passengers[0].IsSittingInVehicle(this.game_Bus))
				{
					Gameplay.PlaySpeech(Gameplay.Player, "GENERIC_HI");
					Gameplay.PlaySpeech(this.game_RouteInfo[this.game_RouteIndex].BusStops[this.game_CurrentStop].Passengers[0], "GENERIC_HI");
				}
				if (this.game_WarpTimer.Finished && !this.game_PositionFix && Gameplay.DoesPedExist(this.game_RouteInfo[this.game_RouteIndex].BusStops[this.game_CurrentStop].Passengers[0]))
				{
					if (this.game_RouteInfo[this.game_RouteIndex].BusStops[this.game_CurrentStop].Passengers[0].IsStopped)
					{
						if (!this.game_PositionFixMessage)
						{
							UI.Notify("~b~You ~w~have stopped ~y~too close~w~ to sidewalk or edge. This will bug ~y~passengers ~w~behaviour !");
							this.game_PositionFixMessage = true;
						}
						Vector3 offsetInWorldCoords = this.game_Bus.GetOffsetInWorldCoords(new Vector3(-1f, 0f, 0f));
						this.game_Bus.Position = offsetInWorldCoords;
						this.game_PositionFix = true;
						return;
					}
					this.game_PositionFix = true;
				}
				if (this.game_RouteInfo[this.game_RouteIndex].BusStops[this.game_CurrentStop].AreAllPassengersInBus())
				{
					this.CloseBusDoors();
					this.game_CurrentStop++;
					this.game_Bus.FreezePosition = false;
					this.game_RouteProcess = Main.GameProcess.PrepareNextBusStop;
					return;
				}
				break;
			case Main.GameProcess.UnwarpPassengersAtStop:
				this.KeepBusDoorsOpen();
				if (this.IsBusEmpty())
				{
					this.game_PositionFix = false;
					this.game_WarpTimer.Setup(2000);
					this.game_RouteProcess = Main.GameProcess.WaitForPassengersEnter;
					return;
				}
				if (this.game_UnwarpTimer.Finished && this.game_RemovePassengers)
				{
					if (this.game_CurrentStop == 0)
					{
						this.game_RouteInfo[this.game_RouteIndex].BusStops[0].ClearPassengersFromBus();
					}
					else
					{
						this.game_RouteInfo[this.game_RouteIndex].BusStops[this.game_CurrentStop - 1].ClearPassengersFromBus();
					}
					this.game_RemovePassengers = false;
					return;
				}
				break;
			case Main.GameProcess.PrepareNextBusStop:
				this.game_Speech = false;
				this.game_InfoBoard.Show(false);
				Gameplay.ClearArea(this.game_RouteInfo[this.game_RouteIndex].BusStops[this.game_CurrentStop].Position, 20f);
				if (Gameplay.Player.IsSittingInVehicle(this.game_Bus))
				{
					this.StartNavigation(this.game_RouteInfo[this.game_RouteIndex].BusStops[this.game_CurrentStop].Position);
				}
				this.game_RouteProcess = Main.GameProcess.DriveToBusStop;
				return;
			case Main.GameProcess.FinishRoute:
				if (Gameplay.IsVehicleAt(this.game_Bus, this.game_RouteInfo[this.game_RouteIndex].SpawnPosition, 10f) && this.game_Bus.IsStopped)
				{
					this.FinishRoute();
				}
				break;
			default:
				return;
			}
		}

		// Token: 0x0600001A RID: 26 RVA: 0x00003234 File Offset: 0x00001434
		public void RouteProcess()
		{
			if (this.game_DisableScript)
			{
				return;
			}
			if (!this.game_RouteRunning)
			{
				return;
			}
			if (!Gameplay.DoesCarExist(this.game_Bus) || !this.game_Bus.IsDriveable)
			{
				UI.ShowSubtitle("~y~Route~w~ cancelled, ~b~bus~w~ got ~r~wrecked~w~ !", 8000);
				this.ReleaseRoute();
				return;
			}
			if (!Gameplay.Player.IsSittingInVehicle(this.game_Bus) && !Gameplay.Player.IsNearEntity(this.game_Bus, new Vector3(150f, 150f, 150f)))
			{
				UI.ShowSubtitle("~y~Route~w~ cancelled, ~b~bus~w~ got ~r~abandoned~w~ !", 8000);
				this.ReleaseRoute();
				return;
			}
			if (Gameplay.Player.IsSittingInVehicle(this.game_Bus) && this.game_Bus.CurrentBlip.Exists())
			{
				this.ShowBusBlip(false);
				if (this.game_RouteProcess == Main.GameProcess.FinishRoute)
				{
					this.StartNavigationParking(this.game_RouteInfo[this.game_RouteIndex].SpawnPosition);
				}
				else
				{
					this.StartNavigation(this.game_RouteInfo[this.game_RouteIndex].BusStops[this.game_CurrentStop].Position);
				}
			}
			if (!Gameplay.Player.IsSittingInVehicle(this.game_Bus) && !this.game_Bus.CurrentBlip.Exists())
			{
				this.ShowBusBlip(true);
				this.StopNavigation();
			}
		}

		// Token: 0x0600001B RID: 27 RVA: 0x00003384 File Offset: 0x00001584
		private void FinishRoute()
		{
			this.StopNavigation();
			this.ShowBusBlip(false);
			this.ShowRouteBlips(false);
			Gameplay.Player.Task.LeaveVehicle();
			Game.Player.Money = Game.Player.Money + this.settings_Earnings;
			using (List<RouteInfo>.Enumerator enumerator = this.game_RouteInfo.GetEnumerator())
			{
				while (enumerator.MoveNext())
				{
					RouteInfo routeInfo = enumerator.Current;
					routeInfo.RemoveRoute();
				}
				goto IL_7A;
			}
			IL_74:
			Script.Wait(0);
			IL_7A:
			if (!Gameplay.Player.IsInVehicle())
			{
				this.game_Navigation = null;
				this.game_CurrentStop = 0;
				this.game_RouteBlips = false;
				this.game_DisableScript = false;
				this.game_RouteRunning = false;
				this.game_RouteInfo = new List<RouteInfo>();
				this.game_RouteProcess = Main.GameProcess.Initialize;
				this.CreateRoutes();
				return;
			}
			goto IL_74;
		}

		// Token: 0x0600001C RID: 28 RVA: 0x00003464 File Offset: 0x00001664
		private void ReleaseRoute()
		{
			this.StopNavigation();
			this.ShowBusBlip(false);
			this.ShowRouteBlips(false);
			this.game_RouteInfo[this.game_RouteIndex].ReleaseRoute();
			if (Gameplay.DoesCarExist(this.game_Bus))
			{
				this.game_Bus.MarkAsNoLongerNeeded();
			}
			this.game_RouteIndex = 0;
			this.game_CurrentStop = 0;
			this.game_RouteBlips = false;
			this.game_DisableScript = false;
			this.game_RouteRunning = false;
			this.game_RouteProcess = Main.GameProcess.None;
			this.CreateRoutes();
		}

		// Token: 0x0600001D RID: 29 RVA: 0x000034E8 File Offset: 0x000016E8
		private void CreateRoutes()
		{
			RouteInfo item = new RouteInfo("640 : Paleto Bay", new Coords(146.3618f, 6634.107f, 31.63461f, -165.5378f));
			item.AddBusStop(new ObjectPosition(-51.90217f, 6612.914f, 28.78158f, 0f, 0f, 34.99987f), new ObjectPosition(-49.56219f, 6618.98f, 28.92958f, 0f, 0f, 36.99992f), true);
			item.AddBusStop(new ObjectPosition(-201.5934f, 6449.08f, 30.11338f, 0f, 0f, 53.99986f), new ObjectPosition(-200.6127f, 6455.075f, 30.1031f, 0f, 0f, 54.99989f), true);
			item.AddBusStop(new ObjectPosition(-342.3202f, 6334.762f, 29.00133f, 0f, 0f, 36.99998f), new ObjectPosition(-340.2585f, 6339.164f, 29.09661f, 0f, 0f, 41.99997f), true);
			item.AddBusStop(new ObjectPosition(-419.1425f, 6212.702f, 30.4647f, 0f, 0f, 79.99994f), new ObjectPosition(-421.1057f, 6216.256f, 30.43248f, 0f, 0f, 83.99992f), true);
			item.AddBusStop(new ObjectPosition(-250.8848f, 6272.441f, 30.40695f, 0f, 0f, -139.9998f), new ObjectPosition(-251.2124f, 6266.943f, 30.46041f, 0f, 0f, -134.9999f), true);
			item.AddBusStop(new ObjectPosition(-119.47f, 6402.914f, 30.39678f, 0f, 0f, -138.9999f), new ObjectPosition(-120.0572f, 6398.209f, 30.46461f, 0f, 0f, -135.9998f), true);
			item.AddBusStop(new ObjectPosition(-11.82091f, 6510.098f, 30.50598f, 0f, 0f, -144.0001f), new ObjectPosition(-12.87586f, 6504.682f, 30.55138f, 0f, 0f, -136.9998f), true);
			item.AddBusStop(new ObjectPosition(67.15274f, 6465.248f, 30.35293f, 0f, 0f, 40.99998f), new ObjectPosition(69.46225f, 6469.827f, 30.23628f, 0f, 0f, 42.99998f), true);
			item.AddBusStop(new ObjectPosition(-179.7626f, 6213.129f, 30.20608f, 0f, 0f, 39.99997f), new ObjectPosition(-179.0314f, 6218.144f, 30.37109f, 0f, 0f, 44.99996f), true);
			item.AddBusStop(new ObjectPosition(-339.5132f, 6274.885f, 30.27601f, 0f, 0f, -45.99998f), new ObjectPosition(-334.6236f, 6273.824f, 30.32435f, 0f, 0f, -45.99998f), true);
			item.AddBusStop(new ObjectPosition(-250.1466f, 6388.406f, 29.93625f, 0f, 0f, -159.9998f), new ObjectPosition(-253.1235f, 6384.285f, 29.85485f, 0f, 0f, -156.9998f), true);
			item.AddBusStop(new ObjectPosition(-51.47454f, 6596.659f, 28.6336f, 0f, 0f, -146.9998f), new ObjectPosition(-53.57915f, 6591.304f, 28.76913f, 0f, 0f, -143.9998f), true);
			item.AddBusStop(new ObjectPosition(51.67081f, 6621.105f, 30.48505f, 0f, 0f, 130.9999f), new ObjectPosition(46.89603f, 6622.326f, 30.48196f, 0f, 0f, 132.9998f), false);
			this.game_RouteInfo.Add(item);
			RouteInfo item2 = new RouteInfo("614 : Sandy Shores", new Coords(1984.965f, 3782.469f, 32.1757f, -149.6781f));
			item2.AddBusStop(new ObjectPosition(1919.805f, 3707.495f, 31.50975f, 0f, 0f, 28.99998f), new ObjectPosition(1921.248f, 3712.521f, 31.49224f, 0f, 0f, 26.99998f), true);
			item2.AddBusStop(new ObjectPosition(1714.97f, 3589.972f, 34.31293f, 0f, 0f, 29.99997f), new ObjectPosition(1716.71f, 3594.521f, 34.3042f, 0f, 0f, 28f), true);
			item2.AddBusStop(new ObjectPosition(1717.137f, 3729.346f, 32.78564f, 0f, 0f, -154.0002f), new ObjectPosition(1715.561f, 3724.056f, 32.80714f, 0f, 0f, -152.0001f), true);
			item2.AddBusStop(new ObjectPosition(1918.057f, 3845.708f, 31.38722f, 0f, 0f, -152.0001f), new ObjectPosition(1915.335f, 3841.13f, 31.21778f, 0f, 0f, -150.9997f), true);
			item2.AddBusStop(new ObjectPosition(1919.508f, 3948.549f, 31.4361f, 0f, 0f, -24.99999f), new ObjectPosition(1925.245f, 3949.443f, 31.44906f, 0f, 0f, -28.99998f), true);
			item2.AddBusStop(new ObjectPosition(1594.1f, 3800.765f, 33.79989f, 0f, 0f, 35.99994f), new ObjectPosition(1595.915f, 3805.511f, 33.79745f, 0f, 0f, 42.99989f), true);
			item2.AddBusStop(new ObjectPosition(1805.083f, 3304.729f, 41.44643f, 0f, 0f, 124.9999f), new ObjectPosition(1801.071f, 3306.321f, 41.16f, 0f, 0f, 117.9999f), true);
			item2.AddBusStop(new ObjectPosition(1999.443f, 3098.537f, 46.00773f, 0f, 0f, 149.9998f), new ObjectPosition(1994.762f, 3098.656f, 45.96037f, 0f, 0f, 145.9998f), true);
			item2.AddBusStop(new ObjectPosition(2324.792f, 2977.565f, 46.81207f, 0f, 0f, 154.9998f), new ObjectPosition(2319.844f, 2976.479f, 46.49409f, 0f, 0f, 149.9998f), true);
			item2.AddBusStop(new ObjectPosition(2913.512f, 4172.734f, 49.98618f, 0f, 0f, -84.99993f), new ObjectPosition(2917.816f, 4168.277f, 50.10585f, 0f, 0f, -67.99994f), true);
			item2.AddBusStop(new ObjectPosition(2356.912f, 5106.492f, 46.24534f, 0f, 0f, 39.99999f), new ObjectPosition(2358.15f, 5110.591f, 46.34859f, 0f, 0f, 44.99997f), true);
			item2.AddBusStop(new ObjectPosition(2065.236f, 5024.383f, 40.00553f, 0f, 0f, -43.99999f), new ObjectPosition(2068.628f, 5024.645f, 39.90638f, 0f, 0f, -19f), true);
			item2.AddBusStop(new ObjectPosition(1905.894f, 5141.57f, 44.06372f, 0f, 0f, 27.99997f), new ObjectPosition(1908.627f, 5146.454f, 43.94806f, 0f, 0f, 38.99997f), true);
			item2.AddBusStop(new ObjectPosition(1657.962f, 4880.78f, 41.04806f, 0f, 0f, 98.99982f), new ObjectPosition(1655.288f, 4883.545f, 40.96913f, 0f, 0f, 96.99989f), true);
			item2.AddBusStop(new ObjectPosition(1698.5f, 4626.302f, 42.32044f, 0f, 0f, 124.9999f), new ObjectPosition(1692.786f, 4629.151f, 42.47047f, 0f, 0f, 118.9999f), true);
			item2.AddBusStop(new ObjectPosition(1984.454f, 4604.697f, 39.81571f, 0f, 0f, -150.0002f), new ObjectPosition(1980.698f, 4600.074f, 39.64712f, 0f, 0f, -157.0002f), true);
			item2.AddBusStop(new ObjectPosition(2363.55f, 4674.653f, 34.93686f, 0f, 0f, 129.9999f), new ObjectPosition(2358.21f, 4676.624f, 34.85912f, 0f, 0f, 131.9998f), true);
			item2.AddBusStop(new ObjectPosition(2444.185f, 4226.44f, 35.98255f, 0f, 0f, 98.99988f), new ObjectPosition(2439.768f, 4231.145f, 35.86779f, 0f, 0f, 98.99992f), true);
			item2.AddBusStop(new ObjectPosition(2478.119f, 4076.857f, 36.82009f, 0f, 0f, 64.99997f), new ObjectPosition(2476.229f, 4083.019f, 36.96491f, 0f, 0f, 66.99994f), true);
			item2.AddBusStop(new ObjectPosition(2100.089f, 3749.52f, 31.96081f, 0f, 0f, 25.99998f), new ObjectPosition(2101.998f, 3753.683f, 31.93083f, 0f, 0f, 28.99998f), false);
			this.game_RouteInfo.Add(item2);
			RouteInfo item3 = new RouteInfo("512 : Centrum", new Coords(434.8107f, -585.303f, 28.49471f, -98.98016f));
			item3.AddBusStop(new ObjectPosition(399.5974f, -747.6259f, 28.28553f, 0f, 0f, 89.99977f), new ObjectPosition(395.6796f, -744.0556f, 28.27941f, 0f, 0f, 88.99993f), true);
			item3.AddBusStop(new ObjectPosition(247.0426f, -829.9383f, 28.84298f, 0f, 0f, -20.99998f), new ObjectPosition(252.4204f, -828.0403f, 28.73823f, 0f, 0f, -20f), true);
			item3.AddBusStop(new ObjectPosition(106.2687f, -957.2974f, 28.49615f, 0f, 0f, 69.99997f), new ObjectPosition(104.9835f, -953.0038f, 28.54762f, 0f, 0f, 69.99994f), true);
			item3.AddBusStop(new ObjectPosition(197.394f, -1081.93f, 28.29406f, 0f, 0f, 84.99996f), new ObjectPosition(193.6411f, -1078.229f, 28.29406f, 0f, 0f, 85.99991f), true);
			item3.AddBusStop(new ObjectPosition(257.4973f, -1177.393f, 28.51799f, 0f, 0f, 0f), new ObjectPosition(260.795f, -1173.924f, 28.39584f, 0f, 0f, 0f), true);
			item3.AddBusStop(new ObjectPosition(87.79559f, -1450.335f, 28.19555f, 0f, 0f, 45.99995f), new ObjectPosition(88.12967f, -1445.7f, 28.24245f, 0f, 0f, 50.99995f), true);
			item3.AddBusStop(new ObjectPosition(-60.51649f, -1460.293f, 30.97322f, 0f, 0f, 10.99999f), new ObjectPosition(-58.01865f, -1455.61f, 31.1154f, 0f, 0f, 8.999996f), true);
			item3.AddBusStop(new ObjectPosition(-190.2245f, -1615.454f, 32.85874f, 0f, 0f, 85.99992f), new ObjectPosition(-194.1142f, -1612.23f, 32.92382f, 0f, 0f, 85.99997f), true);
			item3.AddBusStop(new ObjectPosition(-90.007f, -1785.146f, 27.75162f, 0f, 0f, 136.9999f), new ObjectPosition(-94.61531f, -1784.533f, 27.93844f, 0f, 0f, 140.9998f), true);
			item3.AddBusStop(new ObjectPosition(137.4198f, -1822.437f, 26.21942f, 0f, 0f, -133.0001f), new ObjectPosition(137.79f, -1825.92f, 26.05f, 5.23255E-06f, 1.999997f, -130.9998f), true);
			item3.AddBusStop(new ObjectPosition(227.3857f, -1738.329f, 27.9874f, 0f, 0f, -140.9998f), new ObjectPosition(225.6988f, -1742.523f, 28.11305f, 0f, 0f, -146.9998f), true);
			item3.AddBusStop(new ObjectPosition(396.6592f, -1778.343f, 28.22147f, 0f, 0f, 139.9999f), new ObjectPosition(391.7884f, -1778.194f, 28.24051f, 0f, 0f, 139.0001f), true);
			item3.AddBusStop(new ObjectPosition(505.3119f, -1743.756f, 27.86801f, 0f, 0f, -109.9999f), new ObjectPosition(507.122f, -1748.378f, 27.74495f, 0f, 0f, -111.9998f), true);
			item3.AddBusStop(new ObjectPosition(516.6769f, -1600.696f, 28.27563f, 0f, 0f, -128.9998f), new ObjectPosition(516.7751f, -1605.935f, 28.31999f, 0f, 0f, -131.0001f), true);
			item3.AddBusStop(new ObjectPosition(405.9883f, -1366.651f, 29.41969f, 0f, 0f, -39.99994f), new ObjectPosition(412.1253f, -1366.436f, 29.10775f, 0f, 0f, -41.99998f), true);
			item3.AddBusStop(new ObjectPosition(234.3909f, -1196.672f, 28.34907f, 0f, 0f, -85.99991f), new ObjectPosition(238.255f, -1200.648f, 28.31784f, 0f, 0f, -83.99989f), true);
			item3.AddBusStop(new ObjectPosition(261.1187f, -973.7057f, 28.33515f, 0f, 0f, -109.9999f), new ObjectPosition(262.1421f, -978.6238f, 28.35717f, 0f, 0f, -110.9999f), true);
			item3.AddBusStop(new ObjectPosition(354.6406f, -708.9678f, 28.27382f, 0f, 0f, -109.9999f), new ObjectPosition(357.2667f, -715.2408f, 28.26788f, 0f, 0f, -109.9999f), false);
			this.game_RouteInfo.Add(item3);
			RouteInfo item4 = new RouteInfo("320 : Airport", new Coords(-865.9067f, -2046.602f, 9.076511f, 134.2896f));
			item4.AddBusStop(new ObjectPosition(-1038.366f, -2065.486f, 12.27092f, 0f, 0f, -46.99996f), new ObjectPosition(-1032.448f, -2066.069f, 12.43438f, 0f, 0f, -44.99998f), true);
			item4.AddBusStop(new ObjectPosition(-1026.941f, -1896.225f, 13.00395f, 0f, 0f, -135.9998f), new ObjectPosition(-1026.601f, -1901.66f, 12.81162f, 0f, 0f, -138.9999f), true);
			item4.AddBusStop(new ObjectPosition(-783.5074f, -1635.501f, 14.29957f, 0f, 0f, -130.9998f), new ObjectPosition(-783.3345f, -1639.37f, 14.3961f, 0f, 0f, -124.9999f), true);
			item4.AddBusStop(new ObjectPosition(-1016.703f, -2479.809f, 12.76147f, 0f, 0f, 56.99993f), new ObjectPosition(-1017.038f, -2475.038f, 12.85441f, 0f, 0f, 58.99996f), true);
			item4.AddBusStop(new ObjectPosition(-1012.695f, -2737.919f, 12.75673f, 0f, 0f, 149.0002f), new ObjectPosition(-1016.012f, -2739.403f, 12.75823f, 0f, 0f, 150.0002f), true);
			item4.AddBusStop(new ObjectPosition(-871.3047f, -2636.054f, 12.96713f, 0f, 0f, -122.9998f), new ObjectPosition(-870.931f, -2641.352f, 12.95558f, 0f, 0f, -121.9998f), true);
			item4.AddBusStop(new ObjectPosition(-725.0393f, -2407.456f, 13.56143f, 0f, 0f, -130.9998f), new ObjectPosition(-724.8851f, -2413.898f, 13.59598f, 0f, 0f, -130.9998f), true);
			item4.AddBusStop(new ObjectPosition(-576.2111f, -2236.31f, 4.907192f, 0f, 0f, -134.9999f), new ObjectPosition(-576.7165f, -2241.397f, 5.0312f, 0f, 0f, -130.9998f), true);
			item4.AddBusStop(new ObjectPosition(-544.5864f, -2079.919f, 6.813038f, 0f, 0f, -47.99998f), new ObjectPosition(-541.1241f, -2080.672f, 6.926042f, 0f, 0f, -45.99995f), true);
			item4.AddBusStop(new ObjectPosition(-783.9774f, -1968.29f, 7.931951f, 0f, 0f, 43.99998f), new ObjectPosition(-783.9735f, -1962.789f, 7.985319f, 0f, 0f, 45f), false);
			this.game_RouteInfo.Add(item4);
			RouteInfo item5 = new RouteInfo("520 : Strawberry", new Coords(267.2766f, -1216.297f, 29.34478f, -89.69343f));
			item5.AddBusStop(new ObjectPosition(143.8483f, -1123.086f, 28.30746f, 0f, 0f, 0f), new ObjectPosition(147.1455f, -1120.126f, 28.31738f, 0f, 0f, 0f), true);
			item5.AddBusStop(new ObjectPosition(131.0919f, -973.5866f, 28.4202f, 0f, 0f, -109.9999f), new ObjectPosition(132.6182f, -977.499f, 28.36856f, 0f, 0f, -110.9998f), true);
			item5.AddBusStop(new ObjectPosition(100.9493f, -776.8359f, 30.48416f, 0f, 0f, -19.99998f), new ObjectPosition(105.0048f, -775.7365f, 30.47268f, 0f, 0f, -19.99999f), true);
			item5.AddBusStop(new ObjectPosition(-348.1023f, -646.6913f, 31.003f, 0f, 0f, 0f), new ObjectPosition(-344.2525f, -644.1283f, 31.16703f, 0f, 0f, 0f), true);
			item5.AddBusStop(new ObjectPosition(-699.6955f, -646.1414f, 30.06682f, 0f, 0f, 0f), new ObjectPosition(-695.8177f, -643.5474f, 30.14879f, 0f, 0f, 0f), true);
			item5.AddBusStop(new ObjectPosition(-1012.42f, -691.2056f, 20.36053f, 0f, 0f, 42.99999f), new ObjectPosition(-1011.01f, -686.1095f, 20.49444f, 0f, 0f, 41.99999f), true);
			item5.AddBusStop(new ObjectPosition(-1256.35f, -884.8185f, 10.92121f, 0f, 0f, 30f), new ObjectPosition(-1254.854f, -879.9107f, 11.0675f, 0f, 0f, 36f), true);
			item5.AddBusStop(new ObjectPosition(-1482.041f, -699.249f, 25.46741f, 0f, 0f, -44.99998f), new ObjectPosition(-1477.58f, -699.1174f, 25.27245f, 0f, 0f, -43.99997f), true);
			item5.AddBusStop(new ObjectPosition(-1879.862f, -378.2677f, 47.46629f, 0f, 0f, -39.99997f), new ObjectPosition(-1875.22f, -378.4749f, 47.14f, -2.000006f, 2.199999f, -39.99997f), true);
			item5.AddBusStop(new ObjectPosition(-2040.672f, -162.0852f, 25.3847f, 0f, 0f, 6.999998f), new ObjectPosition(-2038.065f, -158.2834f, 25.73562f, 0f, 0f, 16.99999f), true);
			item5.AddBusStop(new ObjectPosition(-1722.902f, -711.3094f, 9.079608f, 0f, 0f, 137.0001f), new ObjectPosition(-1728.903f, -709.4695f, 9.082576f, 0f, 0f, 137.9998f), true);
			item5.AddBusStop(new ObjectPosition(-1527.353f, -867.2018f, 9.206707f, 0f, 0f, 155.9999f), new ObjectPosition(-1532.371f, -868.2153f, 9.223173f, 0f, 0f, 155.0002f), true);
			item5.AddBusStop(new ObjectPosition(-1320.714f, -1078.488f, 5.933995f, 0f, 0f, 119.9999f), new ObjectPosition(-1325.618f, -1075.59f, 5.943695f, 0f, 0f, 119.9998f), true);
			item5.AddBusStop(new ObjectPosition(-972.5649f, -1251.597f, 4.508608f, 0f, 0f, -153.0001f), new ObjectPosition(-974.4757f, -1256.347f, 4.583779f, 0f, 0f, -151.9998f), true);
			item5.AddBusStop(new ObjectPosition(-650.0269f, -1049.264f, 16.4095f, 0f, 0f, -129.9999f), new ObjectPosition(-650.5718f, -1054.289f, 16.18822f, 1.06738E-07f, 1.000003f, -135.9998f), true);
			item5.AddBusStop(new ObjectPosition(-570.9269f, -964.5686f, 22.25852f, 0f, 0f, -179.9998f), new ObjectPosition(-574.723f, -967.4758f, 22.10856f, 0f, 0f, 176.9997f), true);
			item5.AddBusStop(new ObjectPosition(-382.8899f, -1139.666f, 28.64762f, 0f, 0f, 165.0002f), new ObjectPosition(-388.4534f, -1142.17f, 28.7038f, 0f, 0f, 164.0002f), true);
			item5.AddBusStop(new ObjectPosition(-38.58197f, -1150.522f, 25.44358f, 0f, 0f, -178.9997f), new ObjectPosition(-42.73892f, -1155.542f, 25.40061f, 1.000003f, 1.5f, -179.9998f), true);
			item5.AddBusStop(new ObjectPosition(169.8549f, -1037.116f, 28.31915f, 0f, 0f, 161.0001f), new ObjectPosition(165.3774f, -1038.633f, 28.32273f, 0f, 0f, 161.0002f), false);
			this.game_RouteInfo.Add(item5);
			RouteInfo item6 = new RouteInfo("526 : Cypress Flats", new Coords(1061.29f, -2446.037f, 28.96568f, 87.23904f));
			item6.AddBusStop(new ObjectPosition(871.7438f, -2449.662f, 27.49677f, 0f, 0f, -5.999997f), new ObjectPosition(875.85f, -2446.145f, 27.64f, 2.001337E-08f, -1.000003f, -6f), true);
			item6.AddBusStop(new ObjectPosition(774.9888f, -2286.054f, 27.6894f, 0f, 0f, -95.99982f), new ObjectPosition(777.8828f, -2290.801f, 27.62f, 7.080016E-06f, 3.000005f, -96.99981f), true);
			item6.AddBusStop(new ObjectPosition(838.679f, -2085.647f, 28.96174f, 0f, 0f, 175.0002f), new ObjectPosition(835.0682f, -2087.952f, 28.94f, 4.003016E-08f, 1.250001f, 173.0001f), true);
			item6.AddBusStop(new ObjectPosition(952.1385f, -1963.195f, 29.31931f, 0f, 0f, -89.9999f), new ObjectPosition(953.9725f, -1966.609f, 29.35f, 1.02335E-05f, 1.000003f, -96.9998f), true);
			item6.AddBusStop(new ObjectPosition(877.5162f, -1742.529f, 28.80683f, 0f, 0f, -15f), new ObjectPosition(881.6197f, -1740.487f, 28.93f, 9.965992E-06f, -0.7500042f, -16f), true);
			item6.AddBusStop(new ObjectPosition(826.3211f, -1499.682f, 27.22159f, 0f, 0f, -68.99992f), new ObjectPosition(831.0577f, -1502.625f, 27.31f, 9.448107E-06f, -1.5f, -66.99993f), true);
			item6.AddBusStop(new ObjectPosition(835.6599f, -1010.475f, 26.09494f, 0f, 0f, 175.0002f), new ObjectPosition(832.9137f, -1014.02f, 25.8403f, 1.048138E-05f, 4.749994f, -177.9999f), true);
			item6.AddBusStop(new ObjectPosition(987.405f, -1038.875f, 40.43398f, 0f, 0f, 70.99995f), new ObjectPosition(984.699f, -1033.953f, 40.72f, 1.000285E-05f, -4f, 77.99982f), true);
			item6.AddBusStop(new ObjectPosition(821.3371f, -1550.754f, 28.63857f, 0f, 0f, 109.9999f), new ObjectPosition(816.4572f, -1548.992f, 28.6f, 1.099746E-05f, 1.749999f, 111.9998f), true);
			item6.AddBusStop(new ObjectPosition(781.6453f, -1905.309f, 28.17392f, 0f, 0f, 74.99996f), new ObjectPosition(778.7909f, -1901.121f, 28.18f, 9.938837E-06f, 0.5000058f, 74.99998f), true);
			item6.AddBusStop(new ObjectPosition(736.2666f, -2238.921f, 28.29524f, 0f, 0f, 84.99995f), new ObjectPosition(732.2202f, -2234.302f, 28.29995f, 0f, 0f, 84.99989f), true);
			item6.AddBusStop(new ObjectPosition(870.4207f, -2462.452f, 27.52462f, 0f, 0f, 174.9998f), new ObjectPosition(865.8249f, -2465.877f, 27.45f, 9.863016E-06f, 1.750053f, 174.0001f), false);
			this.game_RouteInfo.Add(item6);
			RouteInfo item7 = new RouteInfo("594 : El Burro Heights", new Coords(1261.737f, -1970.256f, 43.26155f, -176.0913f));
			item7.AddBusStop(new ObjectPosition(1233.062f, -2087.737f, 43.76808f, 0f, 0f, 108.9998f), new ObjectPosition(1230.083f, -2085.131f, 43.85f, 0.7500094f, 2.75002f, 104.9996f), true);
			item7.AddBusStop(new ObjectPosition(1187.123f, -2537.208f, 35.46434f, 0f, 0f, 14f), new ObjectPosition(1189.503f, -2532.417f, 36.08254f, 1.414661E-05f, -5.250004f, 14.99996f), true);
			item7.AddBusStop(new ObjectPosition(231.8496f, -2918.729f, 4.960552f, 0f, 0f, -107.9998f), new ObjectPosition(232.7208f, -2923.683f, 4.979174f, 0f, 0f, -111.9998f), true);
			item7.AddBusStop(new ObjectPosition(183.4978f, -2604.863f, 5.021871f, 0f, 0f, -11.99999f), new ObjectPosition(189.4076f, -2602.077f, 5.024967f, 0f, 0f, -16.99997f), true);
			item7.AddBusStop(new ObjectPosition(-147.9941f, -2617.117f, 5.00071f, 0f, 0f, 0f), new ObjectPosition(-143.6439f, -2614.461f, 5.00071f, 0f, 0f, -0.9999999f), true);
			item7.AddBusStop(new ObjectPosition(-514.0443f, -2917.166f, 5.000384f, 0f, 0f, -61.99991f), new ObjectPosition(-510.223f, -2919.224f, 5.000385f, 0f, 0f, -44.99992f), true);
			item7.AddBusStop(new ObjectPosition(-423.2273f, -2779.655f, 5.000384f, 0f, 0f, -178.9997f), new ObjectPosition(-428.0035f, -2783.011f, 5.000385f, 0f, 0f, -179.9996f), true);
			item7.AddBusStop(new ObjectPosition(-172.0141f, -2628.72f, 5.001033f, 0f, 0f, -179.9998f), new ObjectPosition(-176.4184f, -2631.85f, 5.025501f, 0f, 0f, -179.9997f), true);
			item7.AddBusStop(new ObjectPosition(257.2532f, -2545.976f, 4.84036f, 0f, 0f, -159.9998f), new ObjectPosition(253.2439f, -2550.082f, 4.841607f, 0f, 0f, -161.9998f), true);
			item7.AddBusStop(new ObjectPosition(368.6216f, -2218.772f, 10.85099f, 0f, 0f, -109.9999f), new ObjectPosition(369.8409f, -2223.962f, 10.48482f, 1.26321E-05f, 4.499997f, -106.9997f), true);
			item7.AddBusStop(new ObjectPosition(693.8801f, -2072.229f, 28.27652f, 0f, 0f, 173.9996f), new ObjectPosition(689.9392f, -2076.708f, 28.27237f, 0f, 0f, 175.0002f), true);
			item7.AddBusStop(new ObjectPosition(904.2889f, -2091.621f, 29.60758f, 0f, 0f, 172.0001f), new ObjectPosition(899.829f, -2093.827f, 29.75953f, 0f, 0f, 175.0002f), true);
			item7.AddBusStop(new ObjectPosition(904.7484f, -2328.058f, 29.48422f, 0f, 0f, 84.99995f), new ObjectPosition(902.5316f, -2323.341f, 29.48003f, 0f, 0f, 83.9999f), true);
			item7.AddBusStop(new ObjectPosition(1041.78f, -2417.454f, 28.2904f, 0f, 0f, -94.99988f), new ObjectPosition(1045.607f, -2421.883f, 28.13f, 1.223128E-05f, 2.500007f, -94.99986f), true);
			item7.AddBusStop(new ObjectPosition(1180.729f, -2087.621f, 41.80404f, 0f, 0f, -165.9997f), new ObjectPosition(1176.119f, -2092.147f, 41.63f, 9.906074E-06f, 2.249996f, -169.9995f), false);
			this.game_RouteInfo.Add(item7);
		}

		// Token: 0x0600001E RID: 30 RVA: 0x000056EC File Offset: 0x000038EC
		private void CreateBus(Coords position)
		{
			this.DeleteBus();
			if (Gameplay.IsPlayerAt(new Coords(-865.9067f, -2046.602f, 9.076511f), 150f))
			{
				this.game_Bus = Gameplay.CreateCar(1283517198, position);
				return;
			}
			this.game_Bus = Gameplay.CreateCar(-713569950, position);
		}

		// Token: 0x0600001F RID: 31 RVA: 0x00005742 File Offset: 0x00003942
		private void DeleteBus()
		{
			if (Gameplay.DoesCarExist(this.game_Bus))
			{
				this.game_Bus.Delete();
			}
		}

		// Token: 0x06000020 RID: 32 RVA: 0x0000575C File Offset: 0x0000395C
		private void CloseBusDoors()
		{
			if (!Gameplay.DoesCarExist(this.game_Bus))
			{
				return;
			}
			this.game_Bus.RightIndicatorLightOn = false;
			this.game_Bus.CloseDoor(0, false);
			this.game_Bus.CloseDoor(1, false);
			this.game_Bus.CloseDoor(2, false);
			this.game_Bus.CloseDoor(3, false);
		}

		// Token: 0x06000021 RID: 33 RVA: 0x000057B8 File Offset: 0x000039B8
		private void OpenBusDoors()
		{
			if (!Gameplay.DoesCarExist(this.game_Bus))
			{
				return;
			}
			this.game_Bus.RightIndicatorLightOn = true;
			this.game_Bus.OpenDoor(0, false, false);
			this.game_Bus.OpenDoor(1, false, false);
			this.game_Bus.OpenDoor(2, false, false);
			this.game_Bus.OpenDoor(3, false, false);
		}

		// Token: 0x06000022 RID: 34 RVA: 0x00005818 File Offset: 0x00003A18
		private void KeepBusDoorsOpen()
		{
			if (!Gameplay.DoesCarExist(this.game_Bus))
			{
				return;
			}
			this.game_Bus.OpenDoor(0, false, false);
			this.game_Bus.OpenDoor(1, false, false);
			this.game_Bus.OpenDoor(2, false, false);
			this.game_Bus.OpenDoor(3, false, false);
		}

		// Token: 0x06000023 RID: 35 RVA: 0x0000586C File Offset: 0x00003A6C
		private bool AreBusDoorsClosed()
		{
			return Gameplay.DoesCarExist(this.game_Bus) && (!this.game_Bus.IsDoorOpen(0) && !this.game_Bus.IsDoorOpen(1) && !this.game_Bus.IsDoorOpen(2) && !this.game_Bus.IsDoorOpen(3));
		}

		// Token: 0x06000024 RID: 36 RVA: 0x000058C4 File Offset: 0x00003AC4
		private bool AreBusDoorsWideOpen()
		{
			return Gameplay.DoesCarExist(this.game_Bus) && (this.game_Bus.GetDoorAngleRatio(0) >= 0.95f && this.game_Bus.GetDoorAngleRatio(3) >= 0.95f && this.game_Bus.GetDoorAngleRatio(2) >= 0.95f && this.game_Bus.GetDoorAngleRatio(3) >= 0.95f);
		}

		// Token: 0x06000025 RID: 37 RVA: 0x0000592F File Offset: 0x00003B2F
		private bool IsBusEmpty()
		{
			return this.game_Bus.IsSeatFree(0) && this.game_Bus.IsSeatFree(1) && this.game_Bus.IsSeatFree(2) && this.game_Bus.IsSeatFree(3);
		}

		// Token: 0x06000026 RID: 38 RVA: 0x0000596C File Offset: 0x00003B6C
		private void EmptyBusWithCountedPassengers()
		{
			int count = this.game_RouteInfo[this.game_RouteIndex].BusStops[this.game_CurrentStop].Passengers.Count;
			int num = this.game_Bus.Passengers.Length;
			UI.ShowSubtitle(string.Concat(new object[]
			{
				"WAITING :  ",
				count,
				"  //\\    INSIDE:  ",
				num
			}), 5000);
		}

		// Token: 0x06000027 RID: 39 RVA: 0x000059EC File Offset: 0x00003BEC
		private string GetBusStopName(int index)
		{
			if (index >= this.game_RouteInfo[this.game_RouteIndex].BusStops.Count)
			{
				return "Terminal";
			}
			return World.GetStreetName(this.game_RouteInfo[this.game_RouteIndex].BusStops[index].Position);
		}

		// Token: 0x06000028 RID: 40 RVA: 0x00005A44 File Offset: 0x00003C44
		private void ShowBusBlip(bool enabled)
		{
			if (!Gameplay.DoesCarExist(this.game_Bus))
			{
				return;
			}
			if (enabled && !this.game_Bus.CurrentBlip.Exists())
			{
				this.game_Bus.AddBlip();
				this.game_Bus.CurrentBlip.IsFlashing = true;
				this.game_Bus.CurrentBlip.Sprite = 513;
				this.game_Bus.CurrentBlip.Color = 2;
				this.game_Bus.CurrentBlip.Name = "Route " + this.game_RouteInfo[this.game_RouteIndex].Name;
			}
			if (!enabled && this.game_Bus.CurrentBlip.Exists())
			{
				this.game_Bus.CurrentBlip.Remove();
			}
		}

		// Token: 0x06000029 RID: 41 RVA: 0x00005B10 File Offset: 0x00003D10
		private void ShowRouteBlips(bool enabled)
		{
			if (enabled)
			{
				foreach (Blip blip in this.game_MissionBlips)
				{
					blip.Remove();
				}
				foreach (RouteInfo routeInfo in this.game_RouteInfo)
				{
					Blip blip2 = World.CreateBlip(new Vector3(routeInfo.SpawnPosition.X, routeInfo.SpawnPosition.Y, routeInfo.SpawnPosition.Z));
					blip2.Sprite = 513;
					blip2.Color = 2;
					blip2.IsShortRange = true;
					blip2.Name = routeInfo.Name;
					this.game_MissionBlips.Add(blip2);
				}
				this.game_RouteBlips = true;
				return;
			}
			foreach (Blip blip3 in this.game_MissionBlips)
			{
				blip3.Remove();
			}
			this.game_RouteBlips = false;
		}

		// Token: 0x0600002A RID: 42 RVA: 0x00005C4C File Offset: 0x00003E4C
		public void StopNavigation()
		{
			if (this.game_Navigation == null)
			{
				return;
			}
			if (this.game_Navigation.Exists())
			{
				this.game_Navigation.Remove();
			}
		}

		// Token: 0x0600002B RID: 43 RVA: 0x00005C75 File Offset: 0x00003E75
		public void StartNavigation(Coords position)
		{
			this.StartNavigation(new Vector3(position.X, position.Y, position.Z));
		}

		// Token: 0x0600002C RID: 44 RVA: 0x00005C94 File Offset: 0x00003E94
		public void StartNavigation(Vector3 position)
		{
			this.StopNavigation();
			this.game_Navigation = World.CreateBlip(position);
			this.game_Navigation.ShowRoute = true;
		}

		// Token: 0x0600002D RID: 45 RVA: 0x00005CB4 File Offset: 0x00003EB4
		public void StartNavigationParking(Coords position)
		{
			this.StartNavigationFinish(new Vector3(position.X, position.Y, position.Z));
		}

		// Token: 0x0600002E RID: 46 RVA: 0x00005CD3 File Offset: 0x00003ED3
		public void StartNavigationFinish(Vector3 position)
		{
			this.StopNavigation();
			this.game_Navigation = World.CreateBlip(position);
			this.game_Navigation.Sprite = 50;
			this.game_Navigation.Color = 66;
			this.game_Navigation.ShowRoute = true;
		}

		// Token: 0x0600002F RID: 47 RVA: 0x00005D10 File Offset: 0x00003F10
		public void LoadSettings()
		{
			string text = AppDomain.CurrentDomain.BaseDirectory + "\\LSTransit.ini";
			if (!File.Exists(text))
			{
				this.CreateSettings();
			}
			this.settings_File = new INIFile(text);
			this.setings_Speech = this.settings_File.ReadBool("player", "Speech");
			this.settings_Earnings = this.settings_File.ReadInt("player", "Payment");
			this.settings_WarpSpeed = this.settings_File.ReadInt("time", "ForceUnwarpFromBus");
		}

		// Token: 0x06000030 RID: 48 RVA: 0x00005DA0 File Offset: 0x00003FA0
		public void CreateSettings()
		{
			string filePath = AppDomain.CurrentDomain.BaseDirectory + "\\LSTransit.ini";
			this.settings_File = new INIFile(filePath);
			this.settings_File.Write("player", "Speech", false);
			this.settings_File.Write("player", "Payment", "150");
			this.settings_File.Write("time", "ForceUnwarpFromBus", "15000");
		}

		// Token: 0x0400000D RID: 13
		private Vehicle game_Bus;

		// Token: 0x0400000E RID: 14
		private Blip game_Navigation;

		// Token: 0x0400000F RID: 15
		private int game_RouteIndex;

		// Token: 0x04000010 RID: 16
		private int game_CurrentStop;

		// Token: 0x04000011 RID: 17
		private bool game_Credits;

		// Token: 0x04000012 RID: 18
		private bool game_Speech;

		// Token: 0x04000013 RID: 19
		private bool game_RouteBlips;

		// Token: 0x04000014 RID: 20
		private bool game_PositionFix;

		// Token: 0x04000015 RID: 21
		private bool game_DisableScript;

		// Token: 0x04000016 RID: 22
		private bool game_RouteRunning;

		// Token: 0x04000017 RID: 23
		private bool game_RemovePassengers;

		// Token: 0x04000018 RID: 24
		private bool game_PositionFixMessage;

		// Token: 0x04000019 RID: 25
		private InfoBoard game_InfoBoard;

		// Token: 0x0400001A RID: 26
		private Timer game_WarpTimer;

		// Token: 0x0400001B RID: 27
		private Timer game_UnwarpTimer;

		// Token: 0x0400001C RID: 28
		private Timer game_InfoBoardTimer;

		// Token: 0x0400001D RID: 29
		private List<Blip> game_MissionBlips;

		// Token: 0x0400001E RID: 30
		private List<RouteInfo> game_RouteInfo;

		// Token: 0x0400001F RID: 31
		private Main.GameProcess game_RouteProcess;

		// Token: 0x04000020 RID: 32
		private INIFile settings_File;

		// Token: 0x04000021 RID: 33
		private bool setings_Speech;

		// Token: 0x04000022 RID: 34
		private int settings_Earnings;

		// Token: 0x04000023 RID: 35
		private int settings_WarpSpeed;

		// Token: 0x0200000E RID: 14
		private enum GameProcess
		{
			// Token: 0x04000048 RID: 72
			Off,
			// Token: 0x04000049 RID: 73
			None,
			// Token: 0x0400004A RID: 74
			Initialize,
			// Token: 0x0400004B RID: 75
			StartRoute,
			// Token: 0x0400004C RID: 76
			DriveToBusStop,
			// Token: 0x0400004D RID: 77
			DriveToBusStopDoorCheck,
			// Token: 0x0400004E RID: 78
			WarpPassengersAtStop,
			// Token: 0x0400004F RID: 79
			WaitForPassengersEnter,
			// Token: 0x04000050 RID: 80
			UnwarpPassengersAtStop,
			// Token: 0x04000051 RID: 81
			PrepareNextBusStop,
			// Token: 0x04000052 RID: 82
			FinishRoute
		}
	}
}
