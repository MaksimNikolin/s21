from loguru import logger

from utils.utils import get_project_root

logger.remove()

log_directory = get_project_root() / "log"
log_directory.mkdir(exist_ok=True)

controller_log = logger.bind(name="controller")
controller_log.add(
    log_directory / "controller.log",
    format=(
        "<green>[{time:YYYY-MM-DD HH:mm:ss}]</green> "
        "<cyan>{file}</cyan>:<cyan>{line}</cyan> "
        "<level>{level: <8}</level>: {message}"
    ),
    level="DEBUG",
    filter=lambda record: record["extra"].get("name") == "controller",
    rotation="10 MB",
    backtrace=True,
    diagnose=True,
)

view_log = logger.bind(name="view")
view_log.add(
    log_directory / "view.log",
    format=(
        "<green>[{time:YYYY-MM-DD HH:mm:ss}]</green> "
        "<cyan>{file}</cyan>:<cyan>{line}</cyan> "
        "<level>{level: <8}</level>: {message}"
    ),
    level="DEBUG",
    filter=lambda record: record["extra"].get("name") == "view",
    rotation="10 MB",
    backtrace=True,
    diagnose=True,
)

domain_log = logger.bind(name="domain")
domain_log.add(
    log_directory / "domain.log",
    format=(
        "<green>[{time:YYYY-MM-DD HH:mm:ss}]</green> "
        "<cyan>{file}</cyan>:<cyan>{line}</cyan> "
        "<level>{level: <8}</level>: {message}"
    ),
    level="DEBUG",
    filter=lambda record: record["extra"].get("name") == "domain",
    rotation="10 MB",
    backtrace=True,
    diagnose=True,
)

# USE:
# from logger import controller_log
# from logger import view_log
# from logger import domain_log
# controller_log.debug("Controller initialized")
# view_log.info("View loaded successfully")
# domain_log.warning("HP is low")
# domain_log.error("Domain error occurred")
# domain_log.critical("Program shut down")
