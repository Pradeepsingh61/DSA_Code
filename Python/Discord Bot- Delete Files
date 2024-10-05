import discord
from discord.ext import commands
import asyncio

intents = discord.Intents.default()
intents.message_content = True

bot = commands.Bot(command_prefix='!', intents=intents)

@bot.event
async def on_ready():
    print(f'{bot.user} has connected to Discord!')

@bot.command(name='delete_all')
@commands.has_permissions(manage_messages=True)
async def delete_all_messages(ctx):
    channel = ctx.channel
    await ctx.send("Deleting all messages in this channel. This may take a while...")
    
    async for message in channel.history(limit=None):
        await message.delete()
        await asyncio.sleep(1)  # To avoid rate limiting
    
    await ctx.send("All messages have been deleted.")

bot.run('YOUR_BOT_TOKEN')
