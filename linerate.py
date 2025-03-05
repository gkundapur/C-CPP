#! /usr/bin/python

def calculate_line_rate(nic_speed_gbps, packet_size_bytes):
  """
  Calculates the theoretical line rate (packets per second) for a given NIC speed and packet size.

  Args:
      nic_speed_gbps: The speed of the NIC in Gigabits per second (Gbps).
      packet_size_bytes: The size of the packet in bytes.

  Returns:
      A tuple containing the line rate (packets per second) and the percentage line rate.
  """

  # Convert Gbps to bps
  nic_speed_bps = nic_speed_gbps * 10**9

  # Convert bytes to bits
  packet_size_bits = packet_size_bytes * 8

  # Calculate line rate
  line_rate_pps = nic_speed_bps / packet_size_bits

  # Calculate percentage line rate
  percentage_line_rate = (line_rate_pps / nic_speed_bps) * 100

  return line_rate_pps, percentage_line_rate

# Define NIC speed and packet size
nic_speed_gbps = 40
packet_size_bytes = 84

# Calculate line rate and percentage
line_rate_pps, percentage_line_rate = calculate_line_rate(nic_speed_gbps, packet_size_bytes)

# Print results
print(f"Theoretical line rate for {packet_size_bytes}-byte packets on {nic_speed_gbps}G NIC:")
print(f"\tPackets per second: {line_rate_pps:.2f}")
print(f"\tPercentage of line rate: {percentage_line_rate:.2f}%")
